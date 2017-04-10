#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char const *argv[])
{
	FSTnode *head_node;
	int stride_size,pos_pfx=0,*LMP, i=0;
	ipv4_pfx a,a1;
	FILE *pfx;
	stride_size = 2;
	a.pfx[0] = 1;
	a.pfx[1] = 1;
	a.netmask = 2;
	a1.pfx[0] = 1;
	a1.pfx[1] = 1;
	a1.pfx[2] = 1;
	a1.pfx[3] = 0;
	a1.pfx[4] = 1;
	a1.pfx[5] = 0;
	a1.netmask = 6;

//	head_node = NewNode(stride_size);
//	head_node = insert(head_node,a,stride_size,&pos_pfx);
//
//	LMP = search(head_node,a1,stride_size,&pos_pfx);
//
//	printf("Prefix = ");
//	for (int j = 0; j < 6; ++j) printf("%d", a1.pfx[j]);
//	printf("\n");
//	printf("LMP = ");
//	if(LMP == NULL) for (int j = 0; j < 32; ++j) printf("0");
//	else {
//		while(*(LMP+i) != -1){
//			printf("%d", *(LMP+i));
//			i++;
//		}
//	}
//	printf("\n");
//
//	pfx = fopen("prefixes", "r");
//	read_prefixes(pfx);
//
//	fclose(pfx);

	return 0;
}
