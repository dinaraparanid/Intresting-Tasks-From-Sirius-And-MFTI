/*
Ограничение по времени: 0.5 секунд
Ограничение по памяти: 256 мегабайт
На планете Татуин снова проходит сражение между армией штурмовиков и повстанцев. Армия
штурмовиков представляет из себя укоплектованный строй из N × M солдат. После продолжительной битвы многие солдаты пали и войска штурмовиков поредели. Максимилиан Вирс всегда
отличался умением вести битвы, и на этот раз у него есть разрушительная стратегия, но для ее
исполнения ему необходимо узнать обстановку в его войске.
Он отправляет одного из коммандеров штурмовиков сесть на гравицикл и пролететь над войском
для его оценки. Если точнее, ему необходимо знать, какой максимальный квадрат его армии остался
уцелевшим. Коммандер видит строй и может сказать о том, в какой точке присутсвует штурмовик,
а в какой — уже пал. Помогите коммандеру найти длину стороны такого максимального квадрата,
где войско осталось целым по данным, которые он вам предоставит.
Формат входных данных
В первой строке даны два натуральных числа N и M (1 6 N, M 6 1000). Далее в N строках расположено по M чисел, разделенных пробелами (число равно 0, если в позиции отсутствует
штурмовик, или 1, если уцелел).
Формат выходных данных
Выведите одно число — сторону максимального квадрата, полностью состоящего из уцелевших
штурмовиков.
Пример
стандартный ввод 
4 5
0 0 0 1 0
0 1 1 1 0
0 0 1 1 0
1 0 1 0 0

стандартный вывод
2
*/

#include <cstdio>
#include <cstdlib>
#include <map>

int main()
{
	int n = 0, m = 0;
	std::scanf("%d%d", &n, &m);

	int** matrix = static_cast<int**>(std::malloc(n * sizeof(int*)));
	for (int i = 0; i < n; i++)
		matrix[i] = static_cast<int*>(std::malloc(m * sizeof(int)));

	for (int i = 0; i < n; i++)
		for (int q = 0; q < m; q++)
			std::scanf("%d", &matrix[i][q]);

	auto** squere = static_cast<std::pair<int, std::pair<int, int>>**>(std::malloc(n * sizeof(std::pair<int, std::pair<int, int>>*)));
	for (int i = 0; i < n; i++)
		squere[i] = static_cast<std::pair<int, std::pair<int, int>>*>(std::malloc(m * sizeof(std::pair<int, std::pair<int, int>>)));

	for (int i = 0; i < n; i++)
		for (int q = 0; q < m; q++)
			squere[i][q].first = 0;

	std::multimap<int, std::pair<int, int>> ones;

	for (int i = 0; i < n; i++)
	{
		for (int q = 0; q < m; q++)
		{
			if (matrix[i][q] == 1)
			{
				int r = 1;

				if (q != 0 && matrix[i][q - 1] == 1)
					r = squere[i][q - 1].second.first - 1;
				else
					while (q + r < m && matrix[i][q + r] == 1)
						r++;

				int d = 1;

				if (i != 0 && matrix[i - 1][q] == 1)
					d = squere[i - 1][q].second.second - 1;
				else
					while (i + d < n && matrix[i + d][q] == 1)
						d++;

				squere[i][q].first = r < d ? r : d;
				squere[i][q].second.first = r;
				squere[i][q].second.second = d;
				
				ones.insert(std::make_pair(squere[i][q].first, std::make_pair(i, q)));
			}
		}
	}

	int ans = 0;

	for (auto it = ones.rbegin(); it != ones.rend(); ++it)
	{
		if (ans >= it->first)
			break;

		const int i = it->second.first;
		const int q = it->second.second;

		int cnt = it->first;

		for (int c = 1; c < cnt; c++)
		{
			if (squere[i + c][q + c].first < squere[i][q].first - c)
			{
				cnt = c;
				break;
			}
		}

		ans = ans > cnt ? ans : cnt;
	}

	std::printf("%d", ans);

	for (int i = 0; i < n; i++)
		std::free(matrix[i]);
	std::free(matrix);

	return 0;
}
