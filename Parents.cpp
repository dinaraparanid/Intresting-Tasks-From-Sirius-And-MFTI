/*Родословная
В генеалогическом древе у каждого человека, кроме родоначальника, есть ровно один родитель.

Каждом элементу дерева сопоставляется целое неотрицательное число, называемое высотой. У родоначальника высота равна 0, у любого другого элемента высота на 1 больше, чем у его родителя.

Вам дано генеалогическое древо, определите высоту всех его элементов.

Входные данные

Программа получает на вход число элементов в генеалогическом древе N. Далее следует N−1 строка, задающие родителя для каждого элемента древа, кроме родоначальника. Каждая строка имеет вид имяпотомка имяродителя.

Выходные данные

Программа должна вывести список всех элементов древа в лексикографическом порядке. После вывода имени каждого элемента необходимо вывести его высоту.

Примечание

Эта задача имеет решение сложности O(n), но вам достаточно написать решение сложности O(n2) (не считая сложности обращения к элементам словаря или ассоциативного массива).


Примеры
Ввод
Вывод
9
Alexei Peter_I
Anna Peter_I
Elizabeth Peter_I
Peter_II Alexei
Peter_III Anna
Paul_I Peter_III
Alexander_I Paul_I
Nicholaus_I Paul_I


Alexander_I 4
Alexei 1
Anna 1
Elizabeth 1
Nicholaus_I 4
Paul_I 3
Peter_I 0
Peter_II 2
Peter_III 2*/


#include <iostream>
#include <map>
#include <string>
#include <queue>

int main()
{
	int n = 0;
	std::scanf("%d", &n);
	std::map<std::string, std::string> family; // сын/отец
	std::map<std::string, int> final; // итог
	std::queue<std::string> pred; // родители
	for (int i = 0; i < n - 1; i++)
	{
		std::string child;
		std::string father;
		std::cin >> child;
		std::cin >> father;
		final[child] = 0;
		final[father] = 0;
		family[child] = father;
		family[father];
	}
	for (auto& it : family)
	{
		if (it.second.empty())
		{
			final[it.first] = 0;
			pred.push(it.first);
			family.erase(it.first);
			break;
		}
	} // нашли родоначальника
	while (!pred.empty())
	{
		std::queue<std::string> del; // удаление потомков из family
		for (auto& it : family)
		{
			if (it.second == pred.front())
			{
				final[it.first] = final[pred.front()] + 1;
				pred.push(it.first);
				del.push(it.first);
			}
		}
		while(!del.empty())
		{
			family.erase(del.front());
			del.pop();
		}
		pred.pop();
	}
	for (auto& it : final)
		std::printf("%s %d\n", it.first.c_str(), it.second);
	return 0;
}