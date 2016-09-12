#include "max_heap.h"

void max_heapify(int* a, int length, int index)
{
	int largest_index = index;	// Set current index element as the largest one
	int l_child = index + 1;	// Set next element as the left child
	int r_child = index + 2;	// Set second element as the right child
	if((l_child < length) && (a[l_child] > a[largest_index]))
	{
		largest_index = l_child;
	}
	if((r_child < length) && (a[r_child] > a[largest_index]))
	{
		largest_index = r_child;	
	}
	if(largest_index != index)
	{
		int tmp = a[index];
		a[index] = a[largest_index];
		a[largest_index] = tmp;
		max_heapify(a, length, largest_index);
	}
	return;
}

void initial_max_heap(int* a, int length)
{
	for(int i = length / 2; i >= 0; i--)
	{
		max_heapify(a, length, i);
	}
	return;
}

