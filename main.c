#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char const *argv[])
{
	FSTnode *head_node;
	int stride_size,pos_pfx=0;
	int a1[] = {1,1,1,0,1,0,1,1,0};

	stride_size = 3;

	head_node = NewNode(stride_size);
	head_node = insert(head_node,a1,stride_size,&pos_pfx,9);

	return 0;
}