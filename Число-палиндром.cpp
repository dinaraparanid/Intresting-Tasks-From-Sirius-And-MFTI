/*
Число-палиндром
Напишите программу, которая составляет из цифр введённой строки число-палиндром (число, которое читается одинаково слева направо и справа налево) максимальной длины. Если таких чисел несколько, нужно вывести минимальное из них. Все имеющиеся цифры использовать не обязательно, но количество цифр в ответе должно быть максимально возможным.

Входные данные

Входная строка содержит цифры (по крайней мере, одну) и, возможно, другие символы. Длина строки не превосходит 10000 символов.

Выходные данные

Программа должна вывести число-палиндром максимальной длины, которое можно составить из цифр входной строки.

Примеры
Ввод for i:=99921 downto 2
Вывод 29192
*/

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

int main()
{
	std::string input;
	std::getline(std::cin, input);
	std::map<char, int> collect;
	std::list<char> ans;
	bool can = false;
	
	for (char i : input)
	{
	    if (i > 47 && i < 58)
	    {
	    	if (collect.find(i) != collect.end())
	    	{
			    collect[i]++;
			    if (i != '0')
			    	can = true;
	    	}
		    else
		    	collect.insert({i, 1});
	    }
	}
	
	auto it_ans = ans.begin();
	auto it_collect = collect.begin();
	
	auto place = [&ans, &it_ans](std::map<char, int>::iterator it_collect)
	{
		ans.insert(it_ans, (it_collect->first));
		--it_ans;
		ans.insert(it_ans, (it_collect->first));
	};
	
	if (collect.begin()->first == '0')
	{
		if (collect.size() == 1 || !can)
		{
			putchar('0');
			return 0;
		}
		auto iter = std::next(collect.begin());
		while (iter->second == 1) ++iter;
		place(iter);
		iter->second -= 2;
	}
	
	while (!collect.empty())
	{
		if (it_collect == collect.end())
		{
			ans.insert(it_ans, collect.begin()->first);
			break;
		}
		if (it_collect->second % 2 == 0)
		{
			for (int i = 0; i < it_collect->second; i += 2)
				place(it_collect);
			collect.erase(it_collect++);
		}
		else
		{
			if (it_collect->second > 1)
			{
				int i = 0;
				for (; i < it_collect->second - 1; i += 2)
					place(it_collect);
				it_collect->second -= i;
				++it_collect;
			}
			else ++it_collect;
		}
	}
	
	std::vector<char> ans_vec(ans.size());
	std::move(ans.begin(), ans.end(), ans_vec.begin());
	
	for (char i : ans_vec)
		std::printf("%c", i);
	
	return 0;
}
