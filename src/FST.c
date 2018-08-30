#include <stdio.h>
#include <stdlib.h>
#include "FST.h"
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

/* Function responsible for print how to run the program */
void print_usage(char *argv[]){
	printf("Usage: %s stride_size <file1> <file2> num_addrs thread_count num_exec", argv[0]);
	printf("\n");
	printf("stride_size - size of prefix in each node(must be a multipe of 24 and 32)\n");
	printf("<file1> -  prefixes netmask 24/32\n");
	printf("<file2> -  random addresses\n");
	printf("num_addrs  -  number of addresses to be forwarded\n");
	printf("thread_count -  number of threads to execute in parallel\n");
	printf("num_exec  - number of times to execute the program\n");
}

/* Function responsible for allocatin the FST node according to the stride_size */
FSTnode* NewNode(int stride_size){

	int n_entries = 2,i,j;

	for (i = 1; i < stride_size; ++i) n_entries = n_entries*2;

	FSTnode* x = (FSTnode*)malloc(sizeof(FSTnode));
  x->entries = (entry *)malloc(n_entries*sizeof(entry));

  for (i = 0; i < n_entries; ++i){
		x->entries[i].child = NULL;
		for (j = 0; j < 32; ++j) x->entries[i].pfx[j] = -1;
  }

	return x;
}

/* Function responsible for inserting the prefix and the next_hop in the FST */
FSTnode* insert(FSTnode* node,ipv4_pfx *pfx, int stride_size, int *pos_pfx) {

	//Position in which the pfx will be inserted
	int pos = bintodec(pfx,stride_size,pos_pfx);
	int i;

	//If true, end of pfx
	if (31 - *pos_pfx == pfx->netmask){
		for (i = 31; i > 31- pfx->netmask; --i) node->entries[pos].pfx[i] = pfx->pfx[i];
		for (i = 0; i < 4; ++i) node->entries[pos].next_hop[i] = pfx->next_hop[i];
		//Resets the position
		*pos_pfx = 31;
	} else {
		if(node->entries[pos].child != NULL) insert(node->entries[pos].child, \
		pfx,stride_size,pos_pfx);
		else{
			node->entries[pos].child = NewNode(stride_size);
			insert(node->entries[pos].child,pfx,stride_size,pos_pfx);
		}
	}

	return node;
}
/* Function responsible for, given the stride_size, return the correct position in the node entry */
int bintodec(ipv4_pfx *pfx, int stride_size, int *pos_pfx){

	int i,pos = 0,aux=stride_size-1,aux1,aux2 = *pos_pfx, j;

	for (i = *pos_pfx; i > (aux2-stride_size); i--)
	{
		if(pfx->pfx[i] == 1){
			aux1 = 2;
			for (j = 1; j < aux; ++j) aux1 = aux1*2;
			pos = pos+aux1;
		}
		if (i == (aux2-stride_size+1) && pfx->pfx[i] == 1) pos--;
		aux--;
		*pos_pfx = *pos_pfx - 1;
	}

	return pos;
}

/* Function responsible for reading and searching the addrs file  */
ipv4_pfx* read_addr(FILE *addrs_file, int num_addrs){

	assert(addrs_file != NULL);
	ipv4_pfx *addrs;
	uint8_t a0,b0,c0,d0;
	int i=0;

	addrs = malloc(num_addrs*(sizeof(ipv4_pfx)));

	while(i < num_addrs){
		if(fscanf(addrs_file,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8, \
			&a0, &b0, &c0, &d0) == 4){
				addrs[i] = *new_ipv4_prefix(a0,b0,c0,d0);
				addrs[i].next_hop[0] = a0;
				addrs[i].next_hop[1] = b0;
				addrs[i].next_hop[2] = c0;
				addrs[i].next_hop[3] = d0;
				addrs[i].netmask = 31;
				i++;
		} else i = num_addrs;
	}

	return addrs;
}

/*Function responsible for forwarding the addrs*/
float forward(ipv4_pfx *addrs,FSTnode *head_node,int stride_size,int num_addrs,int num_addrs_for, int thread_count, int num_exec){

	int pos_pfx, i=0,j, th_id, num_threads;
	double full_time_omp = 0;
	double full_time_clock = 0;

	double exec_time_omp = omp_get_wtime();
	// printf("%d\n", num_addrs);
	clock_t t;
	t = clock();
	#pragma omp parallel for num_threads(thread_count)
	{
		for(i=0;i<num_addrs;i++){
			// printf("%d\n", addrs[i].netmask);
			pos_pfx = addrs[i].netmask;
			entry *LMP = NULL;
			// printf("%d.%d.%d.%d\n", addrs[i].next_hop[0],addrs[i].next_hop[1], \
			// 			addrs[i].next_hop[2],addrs[i].next_hop[3]);
			// #pragma omp critical
			// {
			LMP = search(head_node,&addrs[i],stride_size,&pos_pfx, LMP);				
			// 	i++;
			// 	if(i >= num_addrs) {
			// 		i = 0;
			// 	}
			// }
			// 	printf("%d.%d.%d.%d ", addrs[i].next_hop[0],addrs[i].next_hop[1], \
			// 			addrs[i].next_hop[2],addrs[i].next_hop[3]);
			// 	printf("Address Binary = ");
			// 	int j;
			// 	// for (j = 31; j >= 0; --j) printf("%d", entry->pfx[j]);
			// 	// printf("\n");
			// 	if(LMP == NULL) printf(" -> (...)\n");
			// 	else {
			// 		int w = 31;
			// 		printf("LMP = ");
			// 		while(LMP->pfx[w] != -1 && w >= 0.0){
			// 			printf("%d", LMP->pfx[w]);
			// 			w--;
			// 		}
			// 		printf("     ->     ");
			// 		printf("%d.%d.%d.%d\n", LMP->next_hop[0], LMP->next_hop[1], LMP->next_hop[2], LMP->next_hop[3]);
			// 	}
			// if(i >= num_addrs) i = 0; 
			//th_id = omp_get_thread_num();
			//printf("#thread id = %d\n", th_id);
			//num_threads = omp_get_num_threads();
			//printf("%d\n", num_threads);
			//printf("%d\n", j);
		}
	} 
	exec_time_omp  = omp_get_wtime() - exec_time_omp;
	// printf("Time measured with omp = %f\n", exec_time_omp);

	return exec_time_omp;
}

/* Function responsible for, given the prefix, return the LMP */
entry* search(FSTnode* node,ipv4_pfx *pfx, int stride_size, int *pos_pfx, entry* found){

	int pos = bintodec(pfx,stride_size,pos_pfx);
	if (pfx->netmask - *pos_pfx == pfx->netmask){
		if(node->entries[pos].pfx[31] != -1) return &node->entries[pos];
	} else {
		if(node->entries[pos].pfx[31] != -1) found = &node->entries[pos];
		if(node->entries[pos].child != NULL) found = search(node->entries[pos].child,pfx,stride_size,pos_pfx, found);
		return found;
	}
	return found;

}

/*Function responsible for reading the prefixes file and the next_hop */
void read_prefixes(FILE *pfxs_file, FSTnode *head_node, int stride_size){

	assert(pfxs_file != NULL);

	uint8_t a0,b0,c0,d0,a1,b1,c1,d1,len;
	int pos_pfx;

	while(fscanf(pfxs_file,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8, \
			&a0, &b0, &c0, &d0) == 4){
		if(fscanf(pfxs_file,"/%"SCNu8, &len) != 1){
			len = 0;
			if(d0 > 0) len = 32;
			else if (c0 > 0) len = 24;
			else if (b0 > 0) len = 16;
			else if (a0 > 0) len = 8;
		}
		if(fscanf(pfxs_file,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8, \
				&a1, &b1, &c1, &d1) != 4){
			printf("Couldn't parse network prefix: "
				"%"PRIu8".%"PRIu8".%"PRIu8".%"PRIu8"/%"PRIu8"\n",
				a0, b0, c0, d0, len);
			exit(1);
		}
		pos_pfx = 31;
		ipv4_pfx *entry = new_ipv4_prefix(a0,b0,c0,d0);
		entry = new_ipv4_addr(a1, b1, c1, d1, entry);
		entry->netmask = len;
		head_node = insert(head_node,entry,stride_size,&pos_pfx);
		free(entry);
	}
}

/* Function responsible for reading the prefixes in decimal base and converting it to binary */
ipv4_pfx* new_ipv4_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d){

	int base,i,j,pos = 31;
	int pfx_dec[4] = {a,b,c,d};

	ipv4_pfx *prefix = malloc(sizeof(ipv4_pfx));

	for(j = 0; j<4; j++){
		a = pfx_dec[j];
		base = 128;
		for(i = 0; i < 8; i++){
			prefix->pfx[pos] = a/base;
			if(prefix->pfx[pos] != 0) a-= base;
			base /= 2;
			pos--;
		}
	}

	return prefix;
}

/* Function responsible for return the next_hop  */
ipv4_pfx* new_ipv4_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d, ipv4_pfx *entry)
{
	entry->next_hop[0] = a;
	entry->next_hop[1] = b;
	entry->next_hop[2] = c;
	entry->next_hop[3] = d;
	return entry;
}

void free_memory(FSTnode* node, int stride_size){

	int i;
	for(i=0;i<pow(2,stride_size);i++){
		if(node->entries[i].child) free_memory(node->entries[i].child, stride_size);
	}
	free(node->entries);
	free(node);

}
