int bubble_sort(int *numbers, int length)
{
	int i, j;
	for(i = 0; i < length; i++)
	{
		for(j = 0; j < length - 1; j++)
		{
			if(numbers[j] > numbers[j + 1])
			{
				int tmp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = tmp;
			}
		}
	}
	return 0;
}
