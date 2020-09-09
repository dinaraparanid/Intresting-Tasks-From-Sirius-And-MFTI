/*
J. Скрытая реклама
Ограничение времени	1 секунда
Ограничение памяти	512Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt
В Антимонопольный комитет Байтландии поступила жалоба от пассажиров метрополитена на то, что в правилах пользования метрополитеном содержится скрытая реклама.
Антимонопольный комитет записал текст правил в одну строку и решил найти наиболее часто встречающуюся в нём подстроку; если таких подстрок несколько — наиболее длинную из них, а если и таких подстрок несколько — лексикографически наименьшую. После чего в случае совпадения ответа с названием какой-нибудь компании будет принято решение о наложении штрафа.
Вам поручено написать программу, которая находит требуемую подстроку.

Формат ввода
Вход состоит из одной непустой строки S, составленной из не более чем 10^6 строчных латинских букв.
Формат вывода
Выведите подстроку, соответствующую требованиям задачи
Пример 1
Ввод	Вывод

zzzz

z


Пример 2
Ввод	Вывод

ibmibmibm

ibm


Пример 3
Ввод	Вывод

hpmetrohp

hp
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main()
{
	std::string input;
	std::cin >> input;

	std::map<char, int> letters;

	for (char ch : input)
	{
		auto it = letters.find(ch);
		if (it != letters.end())
			it->second++;
		else
			letters.insert({ch, 1});
	}

	std::vector<char> answers;
	int max_count = 0;
	
	for (auto p : letters)
		if (p.second > max_count)
			max_count = p.second;

	for (auto p : letters)
		if (p.second == max_count)
			answers.push_back(p.first);
	
	std::vector<std::string> suf_array;
	
	for (char q : answers)
	{
		int ind = input.find(q);
		std::string suf;
		
		for (int s = ind; s < input.size(); s++)
		{
			if (input[s] == q && s > ind) break;
			suf.push_back(input[s]);
		}
		
		for (int i = ind + 1; i < input.size(); i++)
		{
			if (input[i] == q)
			{
				int ptr1 = i;
				int ptr2 = 0;
				int del = 0;
				
				while (ptr2 < suf.size() && ptr1 < input.size() && suf[ptr2] == input[ptr1])
					ptr1++, ptr2++, del++;
				
				const int size = suf.size();
				
				for (int d = 0; d < size - del; d++)
					suf.pop_back();
			}
		}
		suf_array.push_back(suf);
	}
	
	std::sort(suf_array.begin(), suf_array.end(), [](std::string &a, std::string &b) {
		return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	});
	
	int max_size = 0;
	
	for (auto str : suf_array)
		if (str.size() > max_size)
			max_size = str.size();
	
	for (auto str : suf_array)
	{
		if (str.size() == max_size)
		{
			std::puts(str.c_str());
			break;
		}
	}
	
	return 0;
}
