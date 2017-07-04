#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char *argv[])
{
	FSTnode *head_node;
	int stride_size;
	FILE *pfx, *addr;

	if(argc != 4){
		print_usage(argv);
		return 0;
	}

	stride_size = (atoi)(argv[1]);
	pfx = fopen(argv[2], "r");
	addr = fopen(argv[3], "r");
	head_node = NewNode(stride_size);
	read_prefixes(pfx, head_node, stride_size);
	read_addr(addr,head_node,stride_size);

	free_memory(head_node,stride_size);
	fclose(pfx);
	fclose(addr);

	return 0;
}
