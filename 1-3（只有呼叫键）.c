#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int a[15][1000]/*����*/, c[15]/*����µ�����*/;
int n, sum, num;
void shang()
{//�ܹ�����������������or����
	for (; num <= 10; num++)
	{
		if (c[num] != 0 || (sum < 4 && a[num][0] != 0)) printf("%d ", num);
		sum -= c[num]; c[num] = 0;//Ҫͣ�������º���
		while (sum < 4 && a[num][0] != 0) sum++, c[a[num][a[num][0]--]]++, n--;
	}
}
void xia()
{//�ܹ�����������������or����
	for (; num >= 1; num--)
	{
		if (c[num] != 0 || (sum < 4 && a[num][0] != 0)) printf("%d ", num);
		sum -= c[num]; c[num] = 0;//Ҫͣ�������º���
		while (sum < 4 && a[num][0] != 0) sum++, c[a[num][a[num][0]--]]++, n--;
	}
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= 10; i++) a[i][0] = c[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		int st, ed; scanf("%d%d", &st, &ed);
		a[st][++a[st][0]] = ed;
	}
	sum = 0/*����������*/;
	num = 1/*��ǰ¥��*/;
	while (n != 0)
	{
		shang();
		xia();
	}
	shang();
	xia();
	return 0;
}