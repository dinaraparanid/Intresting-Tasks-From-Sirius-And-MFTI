// Подсчитать кол-во паллиндромов для строки

#include <iostream>
#include <string>
#include <vector>

extern inline std::pair<std::vector<int>, std::vector<int>> manaker(const std::string& s)
{
	const int size = s.length();
	std::vector<int> d1(size); // палиндромы нечётной длины 

	int l = 0, r = -1;

	for (int i = 0; i < size; ++i)
	{
		int k = i >= r ? 1 : std::min(d1[l + r - i], r - i + 1);

		while (i + k < size && i - k >= 0 && s[i + k] == s[i - k])  ++k;

		d1[i] = k;

		if (i + k - 1 > r)
			l = i - k + 1, r = i + k - 1;
	}

	std::vector<int> d2(size); // палиндромы чётной длины 

	l = 0, r = -1;

	for (int i = 0; i < size; ++i)
	{
		int k = i > r ? 0 : std::min(d2[l + r - i + 1], r - i + 1);

		while (i + k < size && i - k - 1 >= 0 && s[i + k] == s[i - k - 1])  ++k;

		d2[i] = k;

		if (i + k - 1 > r)
			l = i - k, r = i + k - 1;
	}

	return std::make_pair(d1, d2);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	std::cin >> input;

	const auto vec = manaker(input);

	size_t ans = 0;

	for (auto i : vec.first)
		ans += std::max(0, i - 1);

	for (auto i : vec.second)
		ans += i;

	std::cout << ans;

	return 0;
}
