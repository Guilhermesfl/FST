#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char *argv[])
{
	FSTnode *head_node;
	int stride_size;
	FILE *pfx24,*pfx32, *addr;

	//if(argc != 5){
	//	print_usage(argv);
	//	return 0;
	//}

	stride_size = (atoi)(argv[1]);
	pfx24 = fopen(argv[2], "r");
	//pfx32 = fopen(argv[3], "r");
	addr = fopen(argv[3], "r");
	head_node = NewNode(stride_size);
	read_prefixes(pfx24, head_node, stride_size);
	//read_prefixes(pfx32, head_node, stride_size);
	read_addr(addr,head_node,stride_size);

	fclose(pfx24);
	//fclose(pfx32);
	fclose(addr);

	return 0;
}
