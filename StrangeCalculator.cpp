/*Маленькая девочка Лиза нашла странный автомат для счета. Он состоит из клеток, которые
соединены друг с другом проводками, концы которых помечены символами 􀀀 и +. В каждой клетке
автомата написано либо число, либо операция, либо переменная. В инструкции к автомату она
прочитала, что данные передаются по проводкам от клетки с минусом к клетке с плюсом. В этом
случае будем говорить, что клетка с плюсом зависит от клетки с минусом.
Работает устройство следующим образом:
 результатом вычисления в клетке, которая не помечена ни одним плюсом, является значение,
записанное в неё;
 для всех клеток устройства, сначала вычисляются значения в клетках, от которых зависит
результат вычисления в этой клетке, после чего выполняется операция последовательно для
всех входных данных;
 результат, полученный в клетке с номером 1, является итоговым.
Если в клетке записана операция, то результат ее вычисления зависит от результата не менее
двух других клеток. Если в клетке записана переменная или константа, то она не зависит от ре-
зультата других клеток. Гарантируется, что существует не более одной клетки с переменной и для
любой клетки с умножением существует не более одной цепочки зависимостей из клетки с перемен-
ной. Вычисление всегда завершается.
Лиза решила убедиться в корректности работы вычислителя. Для этого она написала набор
чисел — значений x. Для каждого из этих значений она хочет узнать результат, который должно
выдать устройство. Помогите ей с проверкой.
Формат входных данных
В первой строке входного файла записаны три числа N, M, и Q — количество клеток, количество
зависимостей и количество значений переменной (1 ⩽ N;M;Q ⩽ 105).
Во второй строке записаны N выражений в порядке, соответствующем номерам клеток, в кото-
рых эти выражения записаны:
 + означает, что результат в соответствующей клетке равен сумме значений от которых эта
клетка зависит;
  означает, что результат в соответствующей клетке равен произведению значений в клетках,
от которых данная клетка зависит;
 x означает, что в данной клетке записывается переменная;
 val означает, что в соответствующей клетке записана константа val (1 ⩽ val ⩽ 109 + 8).
В следующих M строках записано по два числа u и v — зависимость клетки v от значения в
клетке u (1 ⩽ u; v ⩽ N, u ̸= v).
В следующих Q строках записаны значения переменной x (0 ⩽ x ⩽ 109 + 8).
Формат выходных данных
В выходной файл выведите Q строк, в каждой из которых по одному числу — результат, по-
лученный на вычислителе для очередного значения x. Так как результат может быть большим,
выведите остаток от деления на 109 + 9.
Система оценки
Баллы за каждую подзадачу начисляются только в случае, если все тесты для этой подзадачи
и необходимых подзадач успешно пройдены.
Страница 5 из 10
I отборочный этап Всесибирской открытой олимпиады школьников по информатике 2020-2021
Новосибирск, 18 октября 2020 года
Подзадача Баллы Ограничения Необходимые
подзадачи
1 23 N;M ⩽ 105;Q ⩽ 100,
от каждой клетки зависит не более 1 клетки
2 24 N;M;Q ⩽ 105,
от каждой клетки зависит не более 1 клетки 1
3 11 N;M;Q ⩽ 105, нет клеток с выражением x
4 42 N;M;Q ⩽ 105 1, 2, 3

Примеры
input.txt output.txt
3 2 2
+ 3 x
2 1
3 1
2
3
5

6


5 6 1
+ + * x 3
2 1
3 1
4 2
4 3
3 2
5 3
2

14
*/

#include <iostream>
#include <vector>
#include <string>

constexpr int del = 1e9 + 9;

uint64_t rec(const std::vector<std::pair<int, int>>& act, const std::vector<std::string>& moves, const int ind, const uint64_t val)
{
	if (moves[ind] == "x")
		return val % del;

	else if (moves[ind] == "+")
		return (rec(act, moves, act[ind].first, val) + rec(act, moves, act[ind].second, val)) % del;

	else if (moves[ind] == "*")
		return (rec(act, moves, act[ind].first, val) * rec(act, moves, act[ind].second, val)) % del;

	else
		return std::stoull(moves[ind]) % del;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n = 0, m = 0, q = 0;
	std::cin >> n >> m >> q;

	std::vector<std::string> moves(n);

	for (auto& mo : moves)
		std::cin >> mo;

	std::vector<std::pair<int, int>> act(n, std::make_pair(-1, -1));

	while (m--)
	{
		std::pair<int, int> p;
		std::cin >> p.first >> p.second;

		if (act[p.second - 1].first == -1)
			act[p.second - 1].first = p.first - 1;
		else
			act[p.second - 1].second = p.first - 1;
	}

	if (q == 0)
		std::cout << rec(act, moves, 0, 0) << '\n';
	else
	{
		while (q--)
		{
			uint64_t elem = 0;
			std::cin >> elem;
			std::cout << rec(act, moves, 0, elem) << '\n';
		}
	}

	return 0;
}