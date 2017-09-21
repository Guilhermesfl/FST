#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char *argv[])
{
	FSTnode *head_node;
	ipv4_pfx *addrs;
	float exec_time=0;
	int stride_size,num_addrs,num_addrs_for,thread_count, num_exec;;
	FILE *pfxs_file, *addrs_file;

	#ifdef __MIC__
		//printf("Running on Intel(R) Xeon(tm) Phi\n");
	#else
		//printf("Running on HOST\n");
	#endif

	/* Checks if number of arguments are correct */
	if(argc != 7){
		print_usage(argv);
		return 0;
	}

	/* Prepares the structures and the command line arguments */
	stride_size = (atoi)(argv[1]);
	head_node = NewNode(stride_size);

	pfxs_file = fopen(argv[2], "r");
	read_prefixes(pfxs_file, head_node, stride_size);

	addrs_file = fopen(argv[3], "r");
	fscanf(addrs_file, "%d", &num_addrs);
	addrs = read_addr(addrs_file,num_addrs);

	num_addrs_for = (atoi)(argv[4]);
	thread_count = (atoi)(argv[5]);
	num_exec = (atoi)(argv[6]);

	/* Forward the addresses*/
	for (int i = 0; i < num_exec; i++) {
		exec_time += forward(addrs,head_node,stride_size,num_addrs,num_addrs_for,thread_count, num_exec);
	}
	exec_time = exec_time/num_exec;
	printf("%d %f %f\n", thread_count,exec_time, num_addrs_for/exec_time);
	//printf("Execute time = %f\n", exec_time);
	//printf("Number of unique addrs forwarded  = %d\n", num_addrs);
	//printf("Total number of addrs forwarded  = %d\n", num_addrs_for);
	//printf("#Addrs/time = %f\n", num_addrs_for/exec_time);

	/* Free all the memory allocated */
	free_memory(head_node,stride_size);
	fclose(pfxs_file);
	fclose(addrs_file);

	return 0;
}
