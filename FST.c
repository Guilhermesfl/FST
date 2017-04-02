#include <stdio.h>
#include <stdlib.h>
#include "FST.h"
#include <string.h>

FSTnode* NewNode(int stride_size){

	int n_entries = 2;
	
	for (int i = 1; i < stride_size; ++i) n_entries = n_entries*2;
	
	FSTnode* x = (FSTnode*)malloc(sizeof(FSTnode));
  	x->entries = (entry *)malloc(n_entries*sizeof(entry));

  	for (int i = 0; i < n_entries; ++i){
		x->entries[i].child = NULL;
  		for (int j = 0; j < 32; ++j) x->entries[i].next_hop[j] = -1;
  	}

	return x; 
}

FSTnode* insert(FSTnode* node,int pfx[], int stride_size, int *pos_pfx, int pfx_size) {
	
	int pos = convert_bin(pfx,stride_size,pos_pfx,pfx_size);
	if (*pos_pfx == pfx_size){ //If true, end of pfx
		for (int i = 0; i < pfx_size; ++i)
		{
			node->entries[pos].next_hop[i] = pfx[i];
		}
		*pos_pfx = 0;
	} else {
		if(node->entries[pos].child != NULL) insert(node->entries[pos].child, \
		pfx,stride_size,pos_pfx,pfx_size);
		else{
			node->entries[pos].child = NewNode(stride_size);
			insert(node->entries[pos].child,pfx,stride_size,pos_pfx,pfx_size);
		}
	}

	return node;
}

int convert_bin(int pfx[], int stride_size, int *pos_pfx, int pfx_size){

	int pos = 0,aux=stride_size-1,aux1,aux2 = *pos_pfx;
	for (int i = *pos_pfx; i < (stride_size+aux2); ++i)
	{
		if(pfx[i] == 1){
			aux1 = 2;
			for (int i = 1; i < aux; ++i) aux1 = aux1*2;
			pos = pos+aux1;
		}
		if (i == (stride_size+aux2-1) && pfx[i] == 1) pos--;
		aux--;
		*pos_pfx = *pos_pfx + 1;
	}

	return pos;
}

int* search(FSTnode* node,int pfx[], int stride_size, int *pos_pfx, int pfx_size){

	int *found;
	int pos = convert_bin(pfx,stride_size,pos_pfx,pfx_size);
	if (*pos_pfx == pfx_size){ //If true, end of pfx
		if(node->entries[pos].next_hop[0] != -1) return node->entries[pos].next_hop;
	} else {
		if(node->entries[pos].next_hop[0] != -1) found = node->entries[pos].next_hop;
		if(node->entries[pos].child != NULL) found = search(node->entries[pos].child,pfx,stride_size,pos_pfx,pfx_size);
		return found;
	}
	
}

void read_prefixes(FILE *pfx){

	uint8_t a0,b0,c0,d0,a1,b1,c1,d1,len;
	uint32_t next_hop,pfx_p;
	fscanf(pfx,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8, \
			&a0, &b0, &c0, &d0);
	fscanf(pfx,"/%"SCNu8, &len);
	len = 32;
	fscanf(pfx,"%"SCNu8".%"SCNu8".%"SCNu8".%"SCNu8, \
			&a1, &b1, &c1, &d1);
	new_ipv4_prefix(a0,b0,c0,d0);
}

void new_ipv4_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d){

	int pfx[8];
	int base;
	base = 128;
	a = c;

	for(int i = 0; i < 8; i++){
		pfx[i] = a/base;
		if(pfx[i] != 0) a-= base;
		base /= 2;
	}

}
