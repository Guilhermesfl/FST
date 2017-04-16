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
	uint32_t next_hop;
	FSTnode *child;
};

struct ipv4_prefix {
	int pfx[32];
	uint32_t next_hop;
	uint8_t netmask;
};

FSTnode* NewNode(int stride_size);
FSTnode* insert(FSTnode* node,ipv4_pfx* pfx, int stride_size, int *pos_pfx);
int convert_bin(ipv4_pfx *pfx, int stride_size, int *pos_pfx);
int* search(FSTnode* node,ipv4_pfx *pfx, int stride_size, int *pos_pfx);
uint32_t new_ipv4_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
ipv4_pfx* new_ipv4_prefix(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
void read_prefixes(FILE *pfxs_file, FSTnode *head_node, int stride_size);
uint32_t new_ipv4_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
