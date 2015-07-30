#include<stdio.h>

int main(int *args, int argv[])
{
	int numbers[10] = {23, 14, 25, 88, 1, 12, 14, 290, 40, 35};
	if(selection_sort(&numbers, sizeof(numbers)/sizeof(int)) == 0)
	{
		printf("Sorted numbers:");
		int i;
		for(i = 0; i < 10; i++)
		{	
			printf(" %d", numbers[i]);
		}
		printf("\n");
	}
	return 0;
}

