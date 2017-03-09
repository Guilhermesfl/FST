#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct fstnode FSTnode;
typedef struct n_entry entry;

struct fstnode{
	entry *entries; 
};

struct n_entry{
	int next_hop[32];
	FSTnode *child;
};

FSTnode* NewNode(int stride_size);
FSTnode* insert(FSTnode* node,int pfx[], int stride_size, int *pos_pfx, int pfx_size);
int convert_bin(int pfx[], int stride_size, int *pos_pfx, int pfx_size);