int selection_sort(int *numbers, int length)
{
	if(!numbers)
	{
		return -1;
	}

	int i, j;
	for(i = 0; i < length - 1; i++)
	{
		int *min = numbers + i;	// Point to the first number that not sorted
		for(j = i + 1; j < length; j++)
		{
			if(numbers[j] < *min)
			{
				min = numbers + j;
			}
		}
		int tmp = *min;
		*min = numbers[i];
		numbers[i] = tmp;
	}
	return 0;
}

