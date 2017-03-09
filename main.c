#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char const *argv[])
{
	FSTnode *head_node;
	int stride_size,pos_pfx;
	int a1[] = {0};
	int a2[] = {0,0,0,0,1};
	int a3[] = {0,0,0,1};
	int a4[] = {0,0,1};
	int a5[] = {0,0,1,0,0,0,0};
	int a6[] = {0,0,1,0,0,0,1};
	int a7[] = {0,0,1,0,1};
	int a8[] = {0,0,1,1,1};
	int a9[] = {1,0};


	stride_size = 1;

	head_node = NewNode(stride_size);
	head_node = insert(head_node,a1,stride_size,&pos_pfx,1);

	return 0;
}