#include <stdio.h>
#include <stdlib.h>
#include "FST.h"
#include <string.h>
#include <assert.h>
/*
*Function responsible for allocatin the FST node according to the stride_size
*/
FSTnode* NewNode(int stride_size){

	int n_entries = 2;
	
	for (int i = 1; i < stride_size; ++i) n_entries = n_entries*2;
	
	FSTnode* x = (FSTnode*)malloc(sizeof(FSTnode));
  	x->entries = (entry *)malloc(n_entries*sizeof(entry));

  	for (int i = 0; i < n_entries; ++i){
		x->entries[i].child = NULL;
  		for (int j = 0; j < 32; ++j) x->entries[i].pfx[j] = -1;
  	}

	return x; 
}
/*
*Function responsible for inserting the prefix and the next_hop in the FST
*/
FSTnode* insert(FSTnode* node,ipv4_pfx *pfx, int stride_size, int *pos_pfx) {
	
	int pos = bintodec(pfx,stride_size,pos_pfx);//Position in which the pfx will be inserted
	if (31 - *pos_pfx == pfx->netmask){ //If true, end of pfx
		for (int i = 31; i > 31- pfx->netmask; --i)
		{
			node->entries[pos].pfx[i] = pfx->pfx[i];
		}
		node->entries[pos].next_hop = pfx->next_hop;
		*pos_pfx = 31; //Resets the position
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
/*
*Function responsible for, given the stride_size, return the correct position in the node entry
*/
int bintodec(ipv4_pfx *pfx, int stride_size, int *pos_pfx){

	int pos = 0,aux=stride_size-1,aux1,aux2 = *pos_pfx;
	for (int i = *pos_pfx; i > (aux2-stride_size); i--)
	{
		if(pfx->pfx[i] == 1){
			aux1 = 2;
			for (int i = 1; i < aux; ++i) aux1 = aux1*2;
			pos = pos+aux1;
		}
		if (i == (aux2-stride_size+1) && pfx->pfx[i] == 1) pos--;
		aux--;
		*pos_pfx = *pos_pfx - 1;
	}

	return pos;
}
/*
*Function responsible for reading and searching the addrs file 
*/
void read_addr(FILE *addrs_file, FSTnode *head_node,int stride_size){

	assert(addrs_file != NULL);

	uint8_t a0,b0,c0,d0;
	int pos_pfx, *LMP = NULL, i, *found = NULL;

	while(fscanf(addrs_file,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8, \
			&a0, &b0, &c0, &d0) == 4){
		pos_pfx = 31;
		ipv4_pfx *entry = new_ipv4_prefix(a0,b0,c0,d0);
		entry->netmask = 31;
		
		LMP = search(head_node,entry,stride_size,&pos_pfx, found);
	
		printf("Prefix = ");
		for (int j = 31; j > 0; --j) printf("%d", entry->pfx[j]);
		printf("\n");
		if(LMP == NULL) {
			printf("No matching prefixes! Default route :\n");
			for (int j = 0; j < 32; ++j) printf("0");
		}else {
			printf("LMP = ");
			while(*(LMP+31) != -1){
				printf("%d", *(LMP+i));
				i--;
			}
		}
		printf("\n");
	}
}
/*
*Function responsible for, given the prefix, return the LMP
*/
int* search(FSTnode* node,ipv4_pfx *pfx, int stride_size, int *pos_pfx, int* found){

	int pos = bintodec(pfx,stride_size,pos_pfx);
	if (31 - *pos_pfx == pfx->netmask){ //If true, end of pfx
		if(node->entries[pos].pfx[31] != -1) return node->entries[pos].pfx;
	} else {
		if(node->entries[pos].pfx[31] != -1) found = node->entries[pos].pfx;
		if(node->entries[pos].child != NULL) found = search(node->entries[pos].child,pfx,stride_size,pos_pfx, found);
		return found;
	}
	return found;
	
}
/*
*Function responsible for reading the prefixes file and the next_hop
*/
void read_prefixes(FILE *pfxs_file, FSTnode *head_node, int stride_size){

	assert(pfxs_file != NULL);

	uint8_t a0,b0,c0,d0,a1,b1,c1,d1,len;
	uint32_t pfx,pfx_p;
	int pos_pfx;

	while(fscanf(pfxs_file,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8, \
			&a0, &b0, &c0, &d0) == 4){
		if(fscanf(pfxs_file,"/%"SCNu8, &len) != 1){
			len = 0;
			if(d0> 0) len = 32;
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
		entry->next_hop = new_ipv4_addr(a1, b1, c1, d1);
		entry->netmask = len;
		head_node = insert(head_node,entry,stride_size,&pos_pfx);
	}
}
/*
*Function responsible for reading the prefixes in decimal base and converting it to binary
*/
ipv4_pfx* new_ipv4_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d){

	int pos = 31;
	int pfx_dec[4] = {a,b,c,d};
	int base;

	ipv4_pfx *prefix = malloc(sizeof(ipv4_pfx));

	for(int j = 0; j<4; j++){
		a = pfx_dec[j];
		base = 128;
		for(int i = 0; i < 8; i++){
			prefix->pfx[pos] = a/base;
			if(prefix->pfx[pos] != 0) a-= base;
			base /= 2;
			pos--;
		}
	}
	
	return prefix;
}
/*
*Function responsible for return the next_hop 
*/
uint32_t new_ipv4_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
     return a << 24 | b << 16 | c << 8 | d;
}
