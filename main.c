#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char const *argv[])
{
	FSTnode *head_node;
	int stride_size,pos_pfx=0,*LMP, i=0;
	int a[] = {1,1};
	int a1[] = {1,1,1,0,1,0};
	FILE *pfx;
	stride_size = 2;

	//head_node = NewNode(stride_size);
	//head_node = insert(head_node,a,stride_size,&pos_pfx,2);

	//LMP = search(head_node,a1,stride_size,&pos_pfx,4);

	//printf("Prefix = ");
	//for (int j = 0; j < 6; ++j) printf("%d", a[j]);
	//printf("\n");
	//printf("LMP = ");
	//if(LMP == NULL) for (int j = 0; j < 32; ++j) printf("0");
	//else {
	//	while(*(LMP+i) != -1){
	//		printf("%d", *(LMP+i));
	//		i++;
	//	}
	//}
	//printf("\n");

	pfx = fopen("prefixes", "r");
	read_prefixes(pfx);

	fclose(pfx);

	return 0;
}
