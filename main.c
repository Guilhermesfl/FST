#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char const *argv[])
{
	FSTnode *head_node;
	int stride_size,*LMP, i=0, pos_pfx = 31;
	FILE *pfx;
	ipv4_pfx *a1 = malloc(sizeof(ipv4_pfx));
	a1->netmask = 2;
	a1->pfx[31] = 0;
	a1->pfx[30] = 0;
	
	stride_size = 2;

	pfx = fopen(argv[1], "r");
	head_node = NewNode(stride_size);
	read_prefixes(pfx, head_node, stride_size);

	LMP = search(head_node,a1,stride_size,&pos_pfx);

	printf("Prefix = ");
	for (int j = 31; j > 0; --j) printf("%d", a1->pfx[j]);
	printf("\n");
	printf("LMP = ");
	if(LMP == NULL) for (int j = 0; j < 32; ++j) printf("0");//DefaultRoute
	else {
		while(*(LMP+31) != -1){
			printf("%d", *(LMP+i));
			i--;
		}
	}
	printf("\n");


	fclose(pfx);

	return 0;
}
