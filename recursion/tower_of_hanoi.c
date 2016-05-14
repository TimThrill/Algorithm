#include <stdio.h>

#define NUM_PLATES 3

/*
 * 1. Move (n - 1) disk from origin axis to middle axis through destination axis
 * 2. Move disk N to destination axis
 * 3. Move (n - 1) disk from middle axis to destination axis through original axis
 */
void hanoi(char origin, char middle, char dest, int numPlates)
{
    if(numPlates > 0)
    {
        hanoi(origin, dest, middle, numPlates - 1);
	printf("Move disk: %d, from %c to %c\n", numPlates, origin, dest);
        hanoi(middle, origin, dest, numPlates - 1);
    }
}

int main()
{
    
    	hanoi('a', 'b', 'c', NUM_PLATES);
	printf("End\n");
	return 0;
}
