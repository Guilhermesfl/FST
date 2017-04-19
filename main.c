#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char const *argv[])
{
	FSTnode *head_node;
	int stride_size = 2;
	FILE *pfx, *addr;

	pfx = fopen(argv[1], "r");
	addr = fopen(argv[2], "r");
	head_node = NewNode(stride_size);
	read_prefixes(pfx, head_node, stride_size);
	read_addr(addr,head_node,stride_size);

	fclose(pfx);
	fclose(addr);

	return 0;
}
