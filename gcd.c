
/* 
 * Euclidean Algorithm
 * gcd(a, b) = gcd(a % b, a)
**/
int gcd(int a, int b)
{
	if(b == 0)
	{
		return -1;
	}
	if(a == b)
	{
		return a;
	}
	else
	{
		return gcd(a % b, a);
	}
}

/*
 * Chinese version
 * gcd(a, b) = gcd( a > b ? a - b : b - a, max(a, b))
**/


int chinese_gcd(int a, int b)
{
	if(a == b)
	{
		return a;
	}
	if(a == 1 || b == 1)
	{
		return 1;
	}
	if(a > b)
	{
		return chinese_gcd(a - b, b);
	}
	else
	{
		return chinese_gcd(b - a, a);
	}
}

/*
 * Hybrid version
 * if a and b are both even, then gcd(a, b) = 2 * gcd(a / 2, b / 2)
 * if a is even and b is odd, then gcd(a, b) = gcd(a / 2, b)
 * if a is odd and b is even, then gcd(a, b) = gcd(a, b / 2)
 * if a and b are both odd, then gcd(a, b) = gcd( a - b || b - a, a || b)
**/
int hybrid_gcd(int a, int b)
{
	if(a < b)
	{
		return hybrid_gcd(b, a);
	}
	else if(a == b)
	{
		return a;
	}

	if(!(a & 1) && !(b & 1))	// a and b are both even
	{
		return (hybrid_gcd(a >> 1, b >> 1) << 1);
	}
	else if(!(a & 1) && (b & 1))	// a is even and b is odd
	{
		return hybrid_gcd(a >> 1, b);
	}
	else if((a & 1) && !(b & 1))	// a is odd and b is even
	{
		return hybrid_gcd(a, b >> 1);
	}
	else	// a and b are both odd
	{
		return hybrid_gcd(a - b, b);
	}
}
