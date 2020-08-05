// Задача про шестиугольные шахматы из вступительной в МФТИ

#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

std::map<char, int> max_high =
{
	{'a', 6},
	{'b', 7},
	{'c', 8},
	{'d', 9},
	{'e', 10},
	{'f', 11},
	{'g', 10},
	{'h', 9},
	{'i', 8},
	{'k', 7},
	{'l', 6},
};

typedef std::pair<char, int> pci;

std::vector<pci> function(const pci fig)
{
	const int max_fig = max_high[fig.first];
	std::vector<pci> p_fig;
	for (int i = fig.second + 1; i <= max_fig; i++)
	{
		p_fig.emplace_back(fig.first, i);
		//printf("1%c%d\n", fig.first, i);
	} // C

	for (int i = fig.second - 1; i > 0; i--)
	{
		p_fig.emplace_back(fig.first, i);
		//printf("2%c%d\n", fig.first, i);
	} // Ю

	int second_ch = 0;
	for (char i = fig.first - 1; i >= 'a'; i--)
	{
		if (i == 'j') i--;
		pci x;
		x.first = i;
		if (x.first >= 'f') second_ch++;
		x.second = fig.second + second_ch;
		if (max_high[x.first] < x.second) break;
		p_fig.push_back(x);
		//printf("3%c%d\n", x.first, x.second);
	} // СЗ

	second_ch = 0;
	for (char i = fig.first + 1; i <= 'l'; i++)
	{
		if (i == 'j') i++;
		pci x;
		x.first = i;
		if (x.first > 'f') second_ch++;
		x.second = fig.second - second_ch;
		if (x.second == 0) break;
		p_fig.push_back(x);
		//printf("4%c%d\n", x.first, x.second);
	} // ЮВ

	second_ch = 0;
	for (char i = fig.first + 1; i <= 'l'; i++)
	{
		if (i == 'j') i++;
		pci x;
		x.first = i;
		if (x.first <= 'f') second_ch++;
		x.second = fig.second + second_ch;
		if (max_high[x.first] < x.second) break;
		p_fig.push_back(x);
		//printf("5%c%d\n", x.first, x.second);
	} // СВ

	second_ch = 0;
	for (char i = fig.first - 1; i >= 'a'; i--)
	{
		if (i == 'j') i--;
		pci x;
		x.first = i;
		if (x.first < 'f') second_ch++;
		x.second = fig.second - second_ch;
		if (x.second == 0) break;
		p_fig.push_back(x);
		//printf("6%c%d\n", x.first, x.second);
	} // ЮЗ
	// перебрали все клетки, в которые может попасть фигура
	return p_fig;
}

int main()
{
	pci fig;
	pci tar;
	std::scanf("%c%d %c%d", &fig.first, &fig.second, &tar.first, &tar.second);
	std::vector<pci> p_fig = function(fig);
	std::vector<pci> p_tar = function(tar);
	int ans = 0;
	for (const auto& i : p_fig)
		if (std::find(p_tar.begin(), p_tar.end(), i) != p_tar.end()) ans++;
	std::printf("%d", ans);
	return 0;
}