#include<stdio.h>
int main()
{
	int n, i;
	for (n = 2; n <= 100; n++)
	{
		int flag = 1;
		for (i = 2; i < n; i++)
			if (n % i == 0) flag = 0;
		if (flag == 1) printf(" %d", n);
	}
	return 0;
}