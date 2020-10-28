/*
Вывести максимальное среднее арифметическое, полученное путём замены 2 чисел на их ср. арифметическое (так делают, не пока останется 1 число)

Пример
Ввод	Вывод
5
1 1 2 1 1

1.25


3
1 2 3

2.25
*/

#include <stdio.h>
#include <malloc.h>

extern inline double mid(const double a, const double b)
{
	return (a + b) / 2;
}

int main()
{
	int n = 0;
	scanf("%d", &n);

	double* pn = malloc(n * sizeof(double));

	for (double* i = pn; i != pn + n; i++)
		scanf("%lf", i);

	double** memo = malloc(n * sizeof(double*));
	for (double** i = memo; i != memo + n; i++)
		*i = malloc(n * sizeof(double));

	for (int i = 0, q = 0; i < n; i++, q++)
		memo[i][q] = pn[i];

	for (int r = 1; r < n; r++)
	{
		for (int i = 0, q = r; q < n; i++, q++)
		{
			double max_res = 0;

			for (int s = r, f = 1; s > 0; s--, f++)
			{
				const double res = mid(memo[i + s][q], memo[i][q - f]);
				if (res > max_res) max_res = res;
			}

			memo[i][q] = max_res;
		}
	}

	printf("%.10lf", (*memo)[n - 1]);

	for (double** i = memo; i != memo + n; i++) free(*i);
	free(memo); free(pn);
	return 0;
}
