#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

extern inline size_t lcp (const std::string& f, const std::string& s)
{
	size_t ans = 0;
	const size_t size = std::min(f.length(), s.length());

	for (size_t i = 0; i < size; i++)
	{
		if (f[i] == s[i]) ans++;
		else break;
	}

	return ans;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	std::cin >> input;
	const size_t size = input.length();

	std::vector<std::string> suf_arr(size, "");

	for (size_t i = 0; i < size; i++)
		for (size_t q = 0; q <= i; q++)
			suf_arr[q].push_back(input[i]);

	std::sort(suf_arr.begin(), suf_arr.end(), [](const std::string& f, const std::string& s) {
		return std::lexicographical_compare(f.begin(), f.end(), s.begin(), s.end());
	});

	size_t ans = suf_arr[0].length();

	for (size_t i = 1; i < size; i++)
		ans += suf_arr[i].length() - lcp(suf_arr[i - 1], suf_arr[i]);

	std::cout << ans;

	return 0;
}
