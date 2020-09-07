/*G. Вторая очередь
Ограничение времени	1 секунда
Ограничение памяти	512Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

В одном из крупнейших городов Байтландии, Байтсбурге, ведётся строительство второй очереди метрополитена. Во время строительства первой очереди были построены 
N
станций, не соединённых между собой. Согласно генеральному плану, метро в Байтсбурге должно состоять не более, чем из двух линий. Каждая линия метро представляет собой прямую.
Президент компании, отвечающей за прокладку линий, хочет убедиться, что можно проложить не более двух линий метро так, чтобы все построенные станции лежали хотя бы на одной из двух линий.

Формат ввода
Первая строка входа содержит одно целое число 
N
 — количество станций (1 ≤ N ≤ 10^5).
Каждая из последующих N строк содержит два целых числа xi и yi, по модулю не превосходящие 10^9 — координаты очередной станции. Гарантируется, что никакие две станции не совпадают.

Формат вывода
Если можно проложить не более двух линий метро так, чтобы все станции оказались хотя бы на одной линии, выведите “ yes”. Иначе выведите “ no”.
Пример 1
Ввод	Вывод
6
0 1
1 1
2 1
0 2
1 3
2 2
no


Пример 2
Ввод	Вывод
6
2 2
4 6
1 0
2 1
6 1
1 1
yes
*/

#include <stdio.h>
#include <malloc.h>

typedef struct dot
{
	long first;
	long second;
} dot;

int k (const dot a, const dot b, const dot checkable)
{
	// (x1−x2)(y3−y2)=(x3−x2)(y1−y2)
	return (a.first - b.first) * (checkable.second - b.second) == (checkable.first - b.first) * (a.second - b.second) ? 1 : 0;
}

int check(const dot* pn, const size_t n)
{
	for (int i = 2; i < n; i++)
		if (!k(pn[i], *pn, pn[1]))
			return 0;
		
	return 1;
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	
	dot* pn = (dot*)malloc(n * sizeof(dot));
	
	for (int i = 0; i < n; i++)
		scanf("%ld%ld", &pn[i].first, &pn[i].second);
	
	dot* second_line1 = (dot*)malloc(1 * sizeof(dot));
	size_t second_size = 0;
	
	size_t wrong = 0;
	
	for (int i = 2; i < n; i++)
	{
		if (!k(*pn, pn[1], pn[i]))
		{
			wrong = i;
			second_line1 = (dot*)realloc(second_line1, ++second_size * sizeof(dot));
			second_line1[second_size - 1] = pn[i];
		}
	}
	
	if (second_size <= 2 || check(second_line1, second_size))
	{
		puts("yes");
		free(second_line1);
		goto END;
	}
	
	else
	{
		free(second_line1);
		second_size = 0;
		
		dot* second_line2 = (dot*)malloc(1 * sizeof(dot));
		size_t wrong2 = 0;
		
		for (int i = 1; i < n; i++)
		{
			if (i == wrong)
				continue;
			
			if (!k(*pn, pn[wrong], pn[i]))
			{
				wrong2 = i;
				second_line2 = (dot*)realloc(second_line2, ++second_size * sizeof(dot));
				second_line2[second_size - 1] = pn[i];
			}
		}
		
		if (second_size <= 2 || check(second_line2, second_size))
		{
			puts("yes");
			free(second_line2);
			goto END;
		}
		
		else
		{
			free(second_line2);
			second_size = 0;
			
			dot* second_line3 = (dot*)malloc(1 * sizeof(dot));
			*second_line3 = *pn;
			
			for (int i = 1; i < n; i++)
			{
				if (i == wrong2)
					continue;
				
				if (!k(*pn, pn[wrong2], pn[i]))
				{
					second_line3 = (dot*)realloc(second_line3, ++second_size * sizeof(dot));
					second_line3[second_size - 1] = pn[i];
				}
			}
			
			if (second_size <= 2 || check(second_line3, second_size))
			{
				puts("yes");
				free(second_line3);
				goto END;
			}
			
			else
			{
				puts("no");
				free(second_line3);
				goto END;
			}
		}
	}
	
END:free(pn);
	return 0;
}
