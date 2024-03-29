#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
const int T = 10;//T个时刻为一个时段
int mymin(int x, int y) { return x < y ? x : y; }
int myabs(int x) { return x < 0 ? -x : x; }
int n, sum/*电梯内人数*/, num/*当前楼层*/, ti[2][15], m[2];
int last/*上一次停靠的楼层*/, time/*上次停靠总用时*/, now/*实时时间*/;
int a[2][15][1500][2]/*上行呼叫时间、目的地*/, b[2][15][1500][2], c[15]/*这层下的人数*/;
int numa[15][1500], numb[15][1500], ab;//用于按呼叫时间降序
int K/*当前处理哪台电梯*/, ans[2][1500][3]/*记录答案*/, _ans[2] = {0,0};
int cmp1(int* x, int* y) { return a[K & 1][ab][*y][0] - a[K & 1][ab][*x][0]; }
int cmp2(int* x, int* y) { return b[K & 1][ab][*y][0] - b[K & 1][ab][*x][0]; }
void checka()
{
	ti[0][10] = a[K & 1][10][numa[10][0]][0];
	for (int i = 9; i >= 1; i--) ti[0][i] = mymin(ti[0][i + 1], a[K & 1][i][numa[i][0]][0]);
}
void checkb()
{
	ti[1][10] = b[K & 1][1][numb[1][0]][0];
	for (int i = 2; i <= 10; i++) ti[1][i] = mymin(ti[1][i - 1], b[K & 1][i][numb[i][0]][0]);
}
bool oka() { return a[K & 1][num][numa[num][0]][0] <= mymin(now, (ti[0][num] / T + 1) * T); }
//上客需要“此时已经呼叫”而且“轮到他的时段”
bool okb() { return b[K & 1][num][numb[num][0]][0] <= mymin(now, (ti[1][num] / T + 1) * T); }
void shang()
{
	for (; num <= 10; num++)
	{
		now = myabs(num - last) + time;
		bool bk = false;
		if (c[num] != 0 || (sum < 4 && oka()))
		{
			bk = true;
			time = now;
			last = num;
			ans[K & 1][++_ans[K & 1]][0] = num;
			ans[K & 1][_ans[K & 1]][1] = time;
		}
		sum -= c[num]; c[num] = 0;//要停靠，先下后上
		while (sum < 4 && a[K & 1][num][numa[num][0]][0] <= now/*蜂拥而上*/)
			sum++, c[a[K & 1][num][numa[num][0]--][1]]++, m[K & 1]--;
		if (bk) ans[K & 1][_ans[K & 1]][2] = sum;
		if (sum == 0 && ti[0][num + 1] > time) return;
	}
}
void xia()
{
	for (; num >= 1; num--)
	{
		now = myabs(num - last) + time;
		bool bk = false;
		if (c[num] != 0 || (sum < 4 && okb()))
		{
			bk = true;
			time = now;
			last = num;
			ans[K & 1][++_ans[K & 1]][0] = num;
			ans[K & 1][_ans[K & 1]][1] = time;
		}
		sum -= c[num]; c[num] = 0;//要停靠，先下后上
		while (sum < 4 && b[K & 1][num][numb[num][0]][0] <= now/*蜂拥而上*/)
			sum++, c[b[K & 1][num][numb[num][0]--][1]]++, m[K & 1]--;
		if (bk) ans[K & 1][_ans[K & 1]][2] = sum;
		if (sum == 0 && ti[1][num - 1] > time) return;
	}
}
void work()
{
	for (ab = 1; ab <= 10; ab++)
	{
		qsort(numa[ab] + 1, numa[ab][0], sizeof(int), cmp1);
		qsort(numb[ab] + 1, numb[ab][0], sizeof(int), cmp2);
	}
	last = num = 1;
	sum = time = 0;
	memset(ti, 0x7f, sizeof(ti));
	while (m[K & 1] != 0)
	{
		checka();
		checkb();
		if (mymin(ti[0][1], ti[1][10]) > time) time = mymin(ti[0][1], ti[1][10]);
		for (int i = 1; i <= 10; i++) if (a[K & 1][i][numa[i][0]][0] <= time)
		{
			num = i;
			shang(); break;
		}
		for (int i = 10; i >= 1; i--) if (b[K & 1][i][numb[i][0]][0] <= time)
		{
			num = i;
			xia(); break;
		}
	}
}
int main()
{
	printf("初始默认电梯都在1楼\n输入总呼叫人数：\n");
	scanf("%d", &n);
	for (int i = 1; i <= 10; i++) numa[i][0] = numb[i][0] = c[i] = 0;
	memset(a, 0x7f, sizeof(a));
	memset(b, 0x7f, sizeof(b));
	m[0] = m[1] = 0;
	for (int i = 1; i <= n; i++)
	{
		int st, ed, t; scanf("%d%d%d", &st, &ed, &t);
		if (st < ed)
			a[ed & 1][st][++numa[st][0]][0] = t, a[ed & 1][st][numa[st][0]][1] = ed,
			numa[st][numa[st][0]] = numa[st][0];
		else b[ed & 1][st][++numb[st][0]][0] = t, b[ed & 1][st][numb[st][0]][1] = ed,
			numb[st][numb[st][0]] = numb[st][0];
		m[ed & 1]++;
	}
	printf("输出格式为停靠楼层+当前时间+启动时人数\n");
	K = 0;work();
	K = 1;work();
	//以下是输出
	while (_ans[0] > m[0] || _ans[1] > m[1])
	{
		if (_ans[0] == m[0])
			m[1]++,printf("1号 %d %d %d\n", ans[1][m[1]][0], ans[1][m[1]][1], ans[1][m[1]][2]);
		else if (_ans[1] == m[1])
			m[0]++, printf("0号 %d %d %d\n", ans[0][m[0]][0], ans[0][m[0]][1], ans[0][m[0]][2]);
		else if(ans[0][m[0] + 1][1]> ans[1][m[1] + 1][1])
			m[1]++, printf("1号 %d %d %d\n", ans[1][m[1]][0], ans[1][m[1]][1], ans[1][m[1]][2]);
		else
			m[0]++, printf("0号 %d %d %d\n", ans[0][m[0]][0], ans[0][m[0]][1], ans[0][m[0]][2]);
	}
	return 0;
}