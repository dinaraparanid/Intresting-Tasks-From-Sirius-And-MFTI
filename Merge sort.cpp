// Реализация сортировки слиянием

#include <stdio.h>
#include <vector>
// Функция сортировки нисходящим слиянием
std::vector<int> merge(std::vector<int> a, std::vector<int> b) 
{
	std::vector<int> res;
    unsigned int i = 0;
    unsigned int j = 0;
    while (i < a.size() && j < b.size())
	    res.push_back(a[i] <= b[j] ? a[i++] : b[j++]);
	while (i < a.size())
        res.push_back(a[i++]);
    while (j < b.size())
        res.push_back(b[j++]);
    return res;
}

std::vector<int> msort(std::vector<int> a)
{
	if (a.size() <= 1)
		return a;
	const auto k = a.size() / 2;
	return merge
	(msort(std::vector<int>(a.begin(), a.begin() + k)),
	 msort(std::vector<int>(a.begin() + k, a.end())));
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    std::vector<int> a(n, 0);
    // Заполняем элементы массива
    for (auto& i : a)
	    scanf("%d", &i);
    std::vector<int>b(n, 0);
    b = msort(a);
    // Выводим отсортированный массив
    for (auto i : b)
	    printf("%d ", i);
    return 0;
}
