/*Прямоугольники
Дана последовательность N прямоугольников различной ширины и высоты (wi,hi). Прямоугольники расположены, начиная с точки (0,0), вправо на оси OX вплотную друг за другом. Требуется найти M — площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой фигуры.

Формат входных данных

В первой строке задано число N (1≤N≤105). Далее идут N строк. В каждой строке содержатся два числа: ширина и высота i-го прямоугольника (1<wi≤3⋅104, 0≤hi≤3⋅104).

Формат выходных данных

Выведите искомое число M.

Примеры
Ввод
Вывод

3
4 3
2 1
2 5

12


3
4 3
2 1
3 5

15
*/﻿


#include <cstdio>
#include <vector>
#include <stack>

typedef long long ll;

int main()
{
	int n = 0;
	std::scanf("%d", &n);
	std::vector<std::pair<int, int>>pn(n + 2);
	pn[0].first = pn[n + 1].first = -1;
	pn[0].second = pn[n + 1].second = 0;
	for (int i = 1; i <= n; i++)
		std::scanf("%d%d", &pn[i].second, &pn[i].first);
	std::vector<int>ans_r(n);
	std::stack<int>st_r;
	st_r.push(0);
	for (int i = 1; i <= n + 1; i++)
	{
		if (pn[i].first >= pn[st_r.top()].first)
			st_r.push(i);
		else
		{
			while (pn[i].first < pn[st_r.top()].first)
			{
				ans_r[st_r.top() - 1] = i == n + 1 ? n : i - 1;
				st_r.pop();
			}
			st_r.push(i);
		}
	}
	std::vector<int>ans_l(n);
	std::stack<int>st_l;
	st_l.push(n + 1);
	for (int i = n; i >= 0; i--)
	{
		if (pn[i].first >= pn[st_l.top()].first)
			st_l.push(i);
		else
		{
			while (pn[i].first < pn[st_l.top()].first)
			{
				ans_l[(st_l.top() - 1)] = i == 0 ? -1 : i - 1;
				st_l.pop();
			}
			st_l.push(i);
		}
	}
	ll max_s = 0;
	std::vector<ll>ph(n + 1);
	ph[0] = 0;
	for (int i = 1; i < n + 1; i++)
		ph[i] = pn[i].second + ph[i - 1];
	for (int i = 0; i < n; i++)
	{
		const ll s = pn[i + 1].first * (ph[ans_r[i]] - ph[ans_l[i] + 1]);
		if (s > max_s) max_s = s;
	}
	std::printf("%lld", max_s);
	return 0;
}