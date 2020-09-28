/*Примерное условие:

Есть девочка Саша, которая играет с папой в города. Они оба знают про друг друга, что запоминают города, которые встречались в матчах (их несколько). Папа всегда проигрывает. Саша хочет понять, папа - дэбил или поддаётся.
Пример:

Входные данные:
3 - кол-во матчей
4 - кол-во слов в матче
... города (Moscow)
...

Нужно вывести unknown, если папа не знал города или название города, если он поддавался*/

#include <iostream>
#include <vector>
#include <set>
#include <map>

int main()
{
	std::map<char, std::set<std::string>> city;
	int n = 0;
	std::scanf("%d", &n);

	while(n--)
	{
		int num = 0;
		std::scanf("%d", &num);

		std::set<std::string>game;
		std::string last;

		for (int i = 0; i < num; i++)
		{
			std::string cit;
			std::cin >> cit;
			last = cit;

			city[cit.front() + 32].insert(cit);
			game.insert(cit);
		}

		bool find = false;

		for (auto it : city[last.back()])
		{
			if (game.find(it) == game.end())
			{
				find = true;
				std::puts(it.c_str());
				break;
			}
		}

		if (!find)
			std::puts("unknown");
	}

	return 0;
} 
