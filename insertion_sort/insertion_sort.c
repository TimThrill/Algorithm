#include"insertion_sort.h"
int insertion_sort(int *numbers, int length)
{
	if(!numbers)
	{
		return -1;
	}

	int i, j;
	for(i = 1; i < length; i++)
	{
		for(j = i; j > 0; j--)
		{
			if(numbers[j] < numbers[j - 1])
			{
				int tmp = numbers[j];
				numbers[j] = numbers[j - 1];
				numbers[j - 1] = tmp;
			} else
			{
				break;	
			}
		}
	}
	return 0;
}
