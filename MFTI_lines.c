/
*G. Вторая очередь
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
#include <stdlib.h>
#include <stdbool.h>

typedef struct dot
{
	int first;
	int second;
} dot;

int compare(const void* a, const void* b)
{
	const dot arg1 = *(const dot*)a;
	const dot arg2 = *(const dot*)b;
	
	if (arg1.first < arg2.first) return -1;
	if (arg1.first > arg2.first) return 1;
	
	if (arg1.second < arg2.second) return -1;
	if (arg1.second > arg2.second) return 1;
	return 0;
}

void fill(dot* pn, const int* n, dot* first_line, size_t* first_size, dot* second_line, size_t* second_size, const size_t* index)
{
	int minus_first = first_line[1].first - first_line->first;
	int minus_second = first_line[1].second - first_line->second;
	
	for (int i = *index; i < *n; i++)
	{
		if (pn[i].first - first_line[*first_size - 1].first != minus_first
		|| pn[i].second - first_line[*first_size - 1].second != minus_second)
		{
			second_line = (dot*)realloc(second_line, ++*second_size * sizeof(dot));
			second_line[*second_size - 1] = pn[i];
		}
		
		else
		{
			first_line = (dot*)realloc(first_line, ++*first_size * sizeof(dot));
			first_line[*first_size - 1] = pn[i];
		}
	}
}

bool check(const dot* second_line, const size_t* second_size)
{
	bool correct = true;
	int minus_first = second_line[1].first - second_line->first;
	int minus_second = second_line[1].second - second_line->second;
	
	for (int i = 3; i < *second_size; i++)
	{
		if (second_line[i].first - second_line[i - 1].first != minus_first
				|| second_line[i].second - second_line[i - 1].second != minus_second)
		{
			correct = false;
			break;
		}
	}
	return correct;
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	
	dot* pn = (dot*)malloc(n * sizeof(int));
	
	for (int i = 0; i < n; i++)
		scanf("%d%d", &pn[i].first, &pn[i].second);
	
	qsort(pn, n, sizeof(dot), compare);
	
	dot* first_line = (dot*)malloc(2 * sizeof(dot));
	dot* second_line = (dot*)malloc(0);
	size_t first_size = 2, second_size = 0;
	
	*first_line = *pn;
	first_line[1] = pn[1];
	
	const size_t index = 2;
	fill(pn, &n, first_line, &first_size, second_line, &second_size, &index);
	
	if (second_size <= 2)
	{
		puts("yes");
		goto END;
	}
	
	else
	{
		if (check(second_line, &second_size))
		{
			puts("yes");
			goto END;
		}
		
		else
		{
			first_size = 2, second_size = 0;
			first_line = (dot*)realloc(first_line, 2 * sizeof(dot));
			second_line = (dot*)realloc(second_line, 1 * sizeof(dot));
			
			*first_line = *pn;
			first_line[1] = pn[2];
			*second_line = pn[1];
			
			const size_t index2 = 3;
			fill(pn, &n, first_line, &first_size, second_line, &second_size, &index2);
			
			if (second_size <= 2)
			{
				puts("yes");
				goto END;
			}
			
			else
			{
				if (check(second_line, &second_size))
				{
					puts("yes");
					goto END;
				}
				
				else
				{
					first_size = 2, second_size = 0;
					first_line = (dot*)realloc(first_line, 2 * sizeof(dot));
					second_line = (dot*)realloc(second_line, 1 * sizeof(dot));
					
					*first_line = pn[1];
					first_line[1] = pn[2];
					*second_line = *pn;
					
					fill(pn, &n, first_line, &first_size, second_line, &second_size, &index2);
					
					if (second_size <= 2)
					{
						puts("yes");
						goto END;
					}
					
					else
					{
						if (check(second_line, &second_size))
						{
							puts("yes");
							goto END;
						}
						
						else
						{
							puts("no");
							goto END;
						}
					}
				}
			}
		}
	}
	
END:free(pn); free(first_line); free(second_line);
	return 0;
} 
