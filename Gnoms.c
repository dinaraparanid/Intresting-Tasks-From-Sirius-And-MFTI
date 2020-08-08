/*
 * Белоснежка и гномы
«Ну не гномы, а наказание какое-то!», — подумала Белоснежка, в очередной раз пытаясь уложить гномов спать. Одного уложишь — другой уже проснулся! И так всю ночь.

У Белоснежки n гномов, и все они очень разные. Она знает, что для того, чтобы уложить спать i-го гнома нужно ai минут, и после этого он будет спать ровно bi минут. Помогите Белоснежке узнать, может ли она получить хотя бы минутку отдыха, когда все гномы будут спать, и если да, то в каком порядке для этого нужно укладывать гномов спать.

Например, пусть есть всего два гнома, a1=1, b1=10, a2=10, b2=20. Если Белоснежка сначала начнет укладывать первого гнома, то потом ей потребуется целых 10 минут, чтобы уложить второго, а за это время проснется первый. Если же она начнет со второго гнома, то затем она успеет уложить первого и получит целых 10 минут отдыха.

Входные данные

Первая строка входных данных содержит число n (1≤n≤105), вторая строка содержит числа a1,a2,… an, третья — числа b1,b2,… bn (1≤ai,bi≤109).

Выходные данные

Выведите n чисел — порядок, в котором нужно укладывать гномов спать. Если Белоснежке отдохнуть не удастся, выведите число −1.

Примеры
Ввод
Вывод
2
1 10
10 20

2 1

----------
 
2
10 10
10 10

-1
 * */

#include <stdio.h>
#include <stdlib.h>

typedef struct gnom
{
	int num;
	int time;
	int dead;
} gnom;

int cmp(const void* a, const void* b)
{
	const gnom arg1 = *(const gnom*)a;
	const gnom arg2 = *(const gnom*)b;
	
	if (arg1.dead + arg1.time < arg2.dead + arg2.time) return -1;
	if (arg1.dead + arg1.time > arg2.dead + arg2.time) return 1;
	return 0;
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	
	gnom* pgnom = (gnom*)malloc(n * sizeof(gnom));
	for (int i = 0; i < n; i++)
		pgnom[i].num = i + 1;
	
	for (int i = 0; i < n; i++)
		scanf("%d", &pgnom[i].time);
	
	for (int i = 0; i < n; i++)
		scanf("%d", &pgnom[i].dead);
	
	qsort(pgnom, n, sizeof(gnom), cmp);
	int min_dead = pgnom[n - 1].dead;

	for (int i = n - 2; i > -1; i--)
	{
		min_dead -= pgnom[i].time;
		if (min_dead <= 0)
		{
			puts("-1");
			goto END;
		}
		if (min_dead > pgnom[i].dead)
			min_dead = pgnom[i].dead;
	}
	
	for (int i = n - 1; i > -1; i--)
		printf("%d ", pgnom[i].num);
	
END:free(pgnom);
	return 0;
}
