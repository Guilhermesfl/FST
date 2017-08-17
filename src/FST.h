#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct fstnode FSTnode;
typedef struct n_entry entry;
typedef struct ipv4_prefix ipv4_pfx;

struct fstnode{
	entry *entries; 
};

struct n_entry{
	int pfx[32];
	int next_hop[4];
	FSTnode *child;
};

struct ipv4_prefix {
	int pfx[32];
	int next_hop[4];
	uint8_t netmask;
};

FSTnode* NewNode(int stride_size);
FSTnode* insert(FSTnode* node,ipv4_pfx* pfx, int stride_size, int *pos_pfx);
int bintodec(ipv4_pfx *pfx, int stride_size, int *pos_pfx);
entry* search(FSTnode* node,ipv4_pfx *pfx, int stride_size, int *pos_pfx, entry* found);
ipv4_pfx* new_ipv4_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
void read_prefixes(FILE *pfxs_file, FSTnode *head_node, int stride_size);
ipv4_pfx* new_ipv4_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d, ipv4_pfx *entry);
ipv4_pfx* read_addr(FILE *addrs_file, int num_addrs);
void forward(ipv4_pfx *addrs,FSTnode *head_node,int stride_size,int num_addrs,int num_addrs_for, int thread_count);
void free_memory(FSTnode* node, int stride_size);
void print_usage(char *argv[]);
