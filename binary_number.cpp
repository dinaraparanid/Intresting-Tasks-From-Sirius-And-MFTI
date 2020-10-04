/*Найдите количество чисел Z, удовлетворяющих неравенству A ≤ Z ≤ B, таких, что в записи Z в двоичной системе счисления используется ровно 2 единицы. Например, если A=10; B=20; то таких чисел 5 (это числа 10=10102; 12=11002; 17=100012; 18=100102; 20=101002).

Входные данные
На вход программы поступают два числа, записанных через пробел — A, B ( 0 ≤ A, B ≤ 109)

Выходные данные
Выведите одно число – количество чисел Z.

Примеры
входные данные
10 20
выходные данные
5*/

#include <cstdio>
#include <deque>

extern inline std::deque<int> toTwo (int num)
{
	std::deque<int> ans;

	if (num == 0)
		ans.push_back(0);

	else
	{
		while (num)
		{
			ans.push_front(num % 2);
			num /= 2;
		}
	}

	return ans;
}

int main()
{
	int a = 1, b = 0; 
	std::scanf("%d%d", &a, &b);

	if (b < 3 || a > b)
		std::putchar('0');

	else
	{
		std::deque<int> start(std::move(toTwo(a)));
		std::deque<int> finish(std::move(toTwo(b)));

		if (start.size() != finish.size())
		{
			size_t ans = 0;

			size_t ind = start.size() - 1;

			for (int i = 1; i != start.size(); i++)
			{
				if (start[i] == 1)
				{
					ind = i;
					break;
				}
			}

			bool find = false;

			for (size_t i = ind + 1; i != start.size(); i++)
			{
				if (start[i] == 1)
				{
					find = true;
					break;
				}
			}

			ans += ind - (find ? 1 : 0);

			size_t size = start.size() + 1;

			while (size < finish.size())
				ans += size++ - 1;

			for (int i = 1; i != finish.size(); i++)
			{
				if (finish[i] == 1)
				{
					ans += finish.size() - i;
					break;
				}
			}

			std::printf("%lld", ans);
		}

		else // start.size() == finish.size()
		{
			if (a == b)
			{
				int cnt = 1;

				for (int i = 1; i != start.size(); i++)
				{
					if (start[i] == 1)
						cnt++;

					if (cnt > 2)
					{
						std::putchar('0');
						return 0;
					}
				}

				std::putchar(cnt == 2 ? '1' : '0');
			}

			else // a != b
			{
				int sind = start.size(), find = finish.size();

				for (int i = 1; i != start.size(); i++)
				{
					if (start[i] == 1)
					{
						sind = i;
						break;
					}
				}

				for (int i = 1; i < finish.size(); i++)
				{
					if (finish[i] == 1)
					{
						find = i;
						break;
					}
				}

				std::printf("%d", sind - find + (sind != start.size() ? 1 : 0));
			}
		}
	}

	return 0;
}  
