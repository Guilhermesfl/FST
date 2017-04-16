#include <stdlib.h>
#include <stdio.h>
#include "FST.h"

int main(int argc, char const *argv[])
{
	FSTnode *head_node;
	int stride_size,pos_pfx=31,*LMP, i=0;
	FILE *pfx;
	stride_size = 8;

	pfx = fopen(argv[1], "r");
	head_node = NewNode(stride_size);
	read_prefixes(pfx, head_node, stride_size);

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

	fclose(pfx);

	return 0;
}
