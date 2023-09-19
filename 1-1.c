#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int myabs(int a) { return a < 0 ? -a : a; }
int main()
{
	int a, b, c; scanf("%d%d%d",&a, &b, &c);
	int sum=0;
	if (a != c)
	{
		printf("%d 0 0\n", c);
		sum += myabs(a - c);
	}
	printf("%d %d 1\n", a, sum);
	sum += myabs(a - b);
	printf("%d %d 0\n", b,sum);
	return 0;
}