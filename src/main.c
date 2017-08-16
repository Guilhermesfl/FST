#include <stdlib.h>
#include <stdio.h>
#include "FST.h"
#include <time.h>

int main(int argc, char *argv[])
{
	FSTnode *head_node;
	ipv4_pfx *addrs;
	int stride_size,num_addrs,num_addrs_for;
	FILE *pfxs_file, *addrs_file;

	if(argc != 5){
		print_usage(argv);
		return 0;
	}


	stride_size = (atoi)(argv[1]);
	head_node = NewNode(stride_size);

	pfxs_file = fopen(argv[2], "r");
	read_prefixes(pfxs_file, head_node, stride_size);

	addrs_file = fopen(argv[3], "r");
	fscanf(addrs_file, "%d", &num_addrs);
	addrs = read_addr(addrs_file,num_addrs);

	num_addrs_for = (atoi)(argv[4]);
	forward(addrs,head_node,stride_size,num_addrs,num_addrs_for);

	free_memory(head_node,stride_size);
	fclose(pfxs_file);
	fclose(addrs_file);

	return 0;
}
