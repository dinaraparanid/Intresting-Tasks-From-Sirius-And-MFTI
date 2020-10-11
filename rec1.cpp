/* По данному числу N выведите все строки длины N из нулей и единиц в лексикографическом порядке. */

#include <cstdio>
#include <vector>

void rec(std::vector<int>& arr, int ind)
{
	if (!ind)
	{
		for (int i : arr)
			std::printf("%d", i);

		std::puts("");
	}

	else
	{
		arr.push_back(0);
		rec(arr, ind - 1);
		arr.pop_back();

		arr.push_back(1);
		rec(arr, ind - 1);
		arr.pop_back();
	}
}

int main ()
{
	int n = 0;
	std::scanf("%d", &n);

	std::vector<int> arr;
	rec(arr, n);

	return 0;
}
