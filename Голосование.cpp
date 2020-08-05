/*Выборы в США
Как известно, в США президент выбирается не прямым голосованием, а путем двухуровневого голосования. Сначала проводятся выборы в каждом штате и определяется победитель выборов в данном штате. Затем проводятся государственные выборы: на этих выборах каждый штат имеет определенное число голосов — число выборщиков от этого штата. На практике, все выборщики от штата голосуют в соответствии с результатами голосования внутри штата, то есть на заключительной стадии выборов в голосовании участвуют штаты, имеющие различное число голосов.

На этот раз вам известно число выборщиков от каждого штата США и результаты голосования каждого гражданина США (а также в каком штате проживает данный гражданин).

Вам необходимо подвести результаты голосования: сначала определить результаты голосования в каждом штате и определить, за какого из кандидатов отданы голоса выборщиков данного штата. Далее необходимо подвести результаты голосования выборщиков по всем штатам.

Входные данные

Первая строка входных данных содержит количество штатов в США N (1≤N≤100000). Далее идет N строк, описывающих штаты США, каждая строка состоит из названия штата и числа выборщиков от этого штата. На следующей строке задано число M (0≤M≤100000)— количество проголосовавших на выборах. В следующих M строках идут записи результатов голосования по каждому из участников голосования. Одна строка соответствует одному избирателю. Записи имеют вид: название штата, имя кандидата, за которого проголосовал данный избиратель. Названия штатов и имена кандидатов не содержат пробелов.

Выходные данные

Выведите список кандидатов, упорядоченный по убыванию числа голосов выборщиков, полученных за данного кандидата, а при равенстве числа голосов выборщиков: в лексикографическом порядке. После имени кандидата выведите число набранных им голосов.

Если в каком-либо штате два или более число кандидатов набрали одинаковое число голосов, то все голоса выборщиков этого штата получает наименьший в лексикографическом порядке кандидат из числа победителей в этом штате.

Гарантируется, что в каждом штате проголосовал хотя бы один избиратель.

Примечание к примерам тестов

В Florida 2 избирателя голосует за Gore и три избирателя за Bush, поэтому 25 голосов выборщиков от Floria получает Bush. В Pennsylvania побеждает Gore (5 голосов против 1), поэтому Gore получает 23 голоса выборщиков от Pennsylvania.

В Florida побеждает Gore (5 голосов выборщиков), в Alaska — Bush (2 голоса выборщика). В Pennsylvania два кандидата набрали наибольшее число голосов (по 1), поэтому 4 голоса выборщиков от этого штата получает Clinton, т.к. он идет раньше в лексикографическом порядке.

Примеры
Ввод
Вывод
2
Florida 25
Pennsylvania 23
11
Florida Gore
Pennsylvania Gore
Florida Bush
Pennsylvania Gore
Pennsylvania Bush
Florida Gore
Pennsylvania Gore
Florida Bush
Pennsylvania Gore
Florida Bush
Pennsylvania Gore

Bush 25
Gore 23


3
Florida 5
Pennsylvania 4
Alaska 3
4
Florida Gore
Pennsylvania Obama
Pennsylvania Clinton
Alaska Bush

Gore 5
Clinton 4
Bush 3
Obama 0*/


#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

typedef long long ll;

bool names_sort (std::pair<std::string, ll>& f, std::pair<std::string, ll>& s)
{
	if (f.second == s.second)
		return std::lexicographical_compare
		(f.first.begin(), f.first.end(),
		s.first.begin(), s.first.end());
	return f.second < s.second;
}

int main()
{
	ll n = 0;
	std::scanf("%lld", &n);
	std::map<std::string, ll> amount; // кол-во голосующих от штатов
	for (ll i = 0; i < n; i++)
	{
		ll voices = 0;
		std::string state;
		std::cin >> state;
		std::scanf("%lld", &voices);
		amount[state] = voices;
	} // заполнили кол-вом голосов
	ll m = 0;
	std::scanf("%lld", &m);
	std::map<std::string, std::map<std::string, ll>> voice; // голосование в штате
	std::map<std::string, ll> victory; // итог (имя, число)
	for (ll i = 0; i < m; i++)
	{
		std::string state;
		std::string guy;
		std::cin >> state;
		std::cin >> guy;
		victory[guy] = 0;
		voice[state][guy]++;
	} // голосование в каждом штате
	std::map<std::string, std::string> guys;
	// победитель в штате (штат, имя)
	for (auto& it : voice) // проход по штату
	{
		std::pair<std::string, ll> max("", -1);
		for (auto& its : it.second)
		{
			if (its.second > max.second)
			{
				max.first = its.first;
				max.second = its.second;
			}
		}
		guys[it.first] = max.first;
	}
	for (auto& guy : guys)
		victory[guy.second] += amount[guy.first];
	std::vector<std::pair<std::string, ll>> print (victory.size());
	// сортировка по значению
	std::copy(victory.begin(), victory.end(), print.begin());
	std::sort(print.rbegin(), print.rend(), names_sort);
	// сортировка значений и анти-сортировка имён
	ll start = 0, finish = 1;
	for (ll i = 0; i < print.size() - 1; i++)
	{
		if (print[i].second != print[i + 1].second)
			start++, finish++;
		else
		{
			while (i < print.size() - 1 && print[i].second == print[i + 1].second)
				finish++, i++;
			std::reverse(print.begin() + start, print.begin() + finish);
			start = finish++;
		}
	} // сортировка имён
	for(auto& i : print)
		std::printf("%s %lld\n", i.first.c_str(), i.second);
	return 0;
}