/*Даётся скобочная последовательность. Нужно вычеркнуть наименьшее кол-во скобок,
что бы образовалась правильная скобочная последовательность. Вывести итоговую последовательность (любую правильную)*/

#include <iostream>
#include <string>
#include <vector>

void rec(const int l, const int r, const std::vector<std::vector<int>>& memo, const std::vector<std::vector<int>>& save, const std::string& input)
{
	if (memo[l][r] == r - l + 1)
		return;

	if (memo[l][r] == 0)
	{
		std::cout << input.substr(l, r - l + 1);
		return;
	}
	
	if (save[l][r] == -1)
	{
		std::cout << input[l];					  // левая скобка
		rec(l + 1, r - 1, memo, save, input); // между 
		std::cout << input[r];					  // правая скобка
		return;
	}
	
	rec(l, save[l][r], memo, save, input);		 // левая подстрока
	rec(save[l][r] + 1, r, memo, save, input); // правая подстрока
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::string input;
	std::cin >> input;

	if (input.length() < 2)
		return 0;

	const int size = input.length();

	std::vector<std::vector<int>> memo (size, std::vector<int>(size));  // дп матрица
	std::vector<std::vector<int>> save (size, std::vector<int>(size));  // хранение индексов c норм разбиением

	for (int r = 0; r < size; r++)
	{
		for (int l = r; l >= 0; l--)
		{
			if (l == r)
				memo[l][r] = 1;
			else
			{
				int best = 1000;  // кол-во удалений
				int bestk = -1;   // оптимальное разбиение
				
				if (input[l] == '(' && input[r] == ')' || input[l] == '{' && input[r] == '}' || input[l] == '[' && input[r] == ']')
					best = memo[l + 1][r - 1];

				for (int k = l; k < r; ++k)
				{
					if (memo[l][k] + memo[k + 1][r] < best)
					{
						best = memo[l][k] + memo[k + 1][r];
						bestk = k;
					}
				}
					
				memo[l][r] = best;
				save[l][r] = bestk;
			}
		}
	}

	rec(0, size - 1, memo, save, input);
	return 0;
}
