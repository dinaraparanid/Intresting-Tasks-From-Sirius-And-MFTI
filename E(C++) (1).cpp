/*
Для пассажиров кольцевой железнодорожной линии, построенной в столице Байтландии, существует следующая система абонементных билетов. Заплатив ai байтландских тугриков, пассажир получает право проезда от станции 0 до станции i (и только до неё). Таким образом, право проезда на две станции i и j даёт абонементный билет стоимостью ai+aj. Так как, кроме станции 0, на кольцевой линии находятся ещё n станций, то всего существует 2^n различных абонементов (включая и бесплатный абонемент со станции 0 до самой себя), отличающиеся множеством станций, до которых они дают проезд.

Вам дана стоимость каждого из 2n абонементов. Требуется восстановить ai или сообщить, что при передаче списка стоимостей абонементов произошла ошибка и ни при каких ai указанные стоимости не могут быть сформированы.

Формат ввода
Первая строка содержит одно целое число n (1 ≤ N ≤ 18) — количество станций (кроме станции 0), находящихся на линии. Каждая их последующих 2n строк содержит одно целое число — стоимость очередного абонемента (0 ≤ p ≤ 228).

Формат вывода
Выведите n целых чисел в неубывающем порядке — значения ai. Если вариантов несколько, выведите любой.

Если решения нет, выведите текст “impossible”.
*/

#include <cstdio>
#include <set>
#include <vector>
#include <cmath>

int main()
{
	std::multiset<int> list;
	int n;
	scanf("%d", &n);
	const int pow_collect = pow(2, n);

	for (int i = 0; i < pow_collect; i++)
	{
		int x;
		scanf("%d", &x);
		list.insert(x);
	}

	bool correct = true;

	const auto zero = list.find(0);
	if (zero != list.end())
		list.erase(list.find(0));
	else correct = false;

	if (!correct) puts("impossible");
	else
	{
		if (n == 1) printf("%d", *list.begin());
		else
		{
			std::vector<int> ans;
			std::vector<int> sums;

			ans.push_back(*list.begin());
			list.erase(list.find(*list.begin()));
			sums.push_back(ans.back());

			ans.push_back(*list.begin());
			list.erase(list.find(*list.begin()));
			sums.push_back(ans.back());

			sums.push_back(ans[0] + ans[1]);
			const auto v1_2 = list.find(sums.back());
			if (v1_2 == list.end()) correct = false;
			else list.erase(v1_2);

			while (correct && ans.size() < n)
			{
				ans.push_back(*list.begin());
				list.erase(list.find(*list.begin()));
				sums.push_back(ans.back());

				const int size = sums.size() - 1;
				for (int i = 0; i < size; i++)
				{
					sums.push_back(sums[i] + ans.back());
					const auto del = list.find(sums.back());
					if (del != list.end())
						list.erase(del);
					else
					{
						correct = false;
						break;
					}
				}
				if (!correct) break;
			}

			if (!correct || !list.empty()) puts("impossible");
			else
				for (int i : ans) 
					printf("%d\n", i);
		}
	}
	return 0;
}