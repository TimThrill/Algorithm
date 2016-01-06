#include"merge_sort.h"

int merge_sort(int *numbers, int length)
{
	if(!numbers)
	{
		return -1;
	}

	int ordered_numbers[length] = {0};
	if(!numbers)
	{
		return -1;
	}
	divide_merge(numbers, length, ordered_numbers);
	return 0;
}

/*
 * This function is to divide the numbers recursively until to a single number,
 * and then reorder them by sequence.
 */
void divide_merge(int *numbers, int length, int *ordered_numbers)
{
	if(length == 1)
	{
		return;
	}

	int mid = length/2;
	divide_merge(numbers, mid, ordered_numbers);	/* Divide the left part*/
	divide_merge(numbers + mid, length - mid, ordered_numbers);	/* Divide the right part */
	merge(numbers, mid, length, ordered_numbers);	/* Merge two parts */
	return;
}

void merge(int *numbers, int mid, int length, int *ordered_numbers)
{
	//Point to left part of numbers and right part of numbers
	int *lpoint = numbers;
	int *rpoint = numbers + mid;
	int lcnt = 0, rcnt = 0;
	while((lcnt < mid) && (rcnt < (length - mid)))
	{
		if(lpoint[lcnt] < rpoint[rcnt])
		{
			ordered_numbers[lcnt + rcnt] = lpoint[lcnt];
			lcnt++;
		}
		else
		{
			ordered_numbers[lcnt + rcnt] = rpoint[rcnt];
			rcnt++;
		}
	}
	if(lcnt == mid)
	{
		for(; rcnt < (length - mid); rcnt++)
		{
			ordered_numbers[lcnt + rcnt] = rpoint[rcnt];
		}
	}
	else
	{
		for(; lcnt < mid; lcnt++)
		{
			ordered_numbers[lcnt + rcnt] = lpoint[lcnt];
		}
	}

	memcpy((void*)numbers, (void*)ordered_numbers, (sizeof(int) * length));
	return;
}

