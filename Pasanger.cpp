#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <iterator>

const int INF = INT_MIN;

class SegmentTree
{
private:
    int last_; // размер
    std::vector<int> builder_; // то, где поддерживаем rmq
    std::vector<int> constructor_; // первоначальный вектор

    int left(int _p) { return _p << 1; } // левая ветвь
    int right(int _p) { return (_p << 1) + 1; }  // правая ветвь

    /**
    Построение дерева отрезков (сегментов).
    @param _p - текущее значение,
    @param _l - текущий индекс влево,
    @param _r - текущий индекс вправо
    */

    void build (int _p, int _l, int _r)
    {
        if (_l == _r)
            builder_[_p] = _l; // дошли до листа
        else
        {
            build(left(_p), _l, (_l + _r) / 2); // строим левую ветвь
            build(right(_p), (_l + _r) / 2 + 1, _r); // строим правую ветвь

            int p1 = builder_[left(_p)], p2 = builder_[right(_p)]; // считаем rmq для права и лева
            builder_[_p] = (constructor_[p1] >= constructor_[p2] ? p1 : p2); // выбираем наибольший результат
        }
    }

    /**
    Нахождение rmq (range minimum query).
    @param _p - текущее значение,
    @param _l - текущий индекс влево,
    @param _r - текущий индекс вправо,
    @return rmq(_i, _j) в ЧАСТИ дерева
    */

    int rmq (int _p, int _l, int _r, int _i, int _j)
    {
        if (_i > _r || _j < _l)  // Если вышли за границу
            throw std::range_error("Index out of range");

        else if (_l >= _i && _r <= _j) // Если попали
            return builder_[_p];

        int p1 = 0, p2 = 0;

        try { p1 = rmq(left(_p), _l, (_l + _r) / 2, _i, _j); } // находим rmq справа
        catch (std::range_error& e)
        {
            p2 = rmq(right(_p), (_l + _r) / 2 + 1, _r, _i, _j);
            return p2;
        }

        try { p2 = rmq(right(_p), (_l + _r) / 2 + 1, _r, _i, _j); } // находим rmq справа
        catch (std::range_error& e) { return p1; }

        return (constructor_[p1] >= constructor_[p2] ? p1 : p2);
    }

public:

    /**
    Конструктор для дерева отрезков.
    @param _vec - вектор, для которого нужно найти rmq
    */

    explicit SegmentTree(const std::vector<int>& _vec)
    {
        constructor_ = _vec;
        last_ = _vec.size();

        builder_.assign(4 * last_, INF);
        build(1, 0, last_ - 1);
    }
    
    /**
    Перестройка дерева. 
    @param _vec - новый вектор
    */

    void rebuild (const std::vector<int>& _vec)
    {
        constructor_ = _vec;
        last_ = _vec.size();

        builder_.assign(4 * last_, INF);
        build(1, 0, last_ - 1);
    }

    int rmq (int _i, int _j) { return rmq(1, 0, last_ - 1, _i, _j); } // перегрузка для нахождения
                                                                          // rmq(_i, _j) для всего дерева
};

int main()
{
	int tests = 0;
	std::scanf("%d", &tests);

	for (int test = 0; test < tests; test++)
	{
		int n = 0, m = 0, x = 0, y = 0, t = 0;
		char act = 0;
		std::scanf("%d%d", &n, &m);

		std::vector<int> pn(n);
		std::vector<size_t> pref(n);

		for (int i = 0; i < n; i++)
		{
			std::scanf("%d", &pn[i]);
			pref[i] = pn[i] + (i > 0 ? pref[i - 1] : 0);
		}

		SegmentTree tree(pn);

		for (int i = 0; i < m; i++)
		{
			std::cin >> act >> x >> y;
			x--, y--;

			switch (act)
			{
            case 'm':
                std::printf("%d\n", pn[tree.rmq(x, y + 1)]);
                break;
            case 's':
                std::printf("%llu\n", pref[y] - (x > 0 ? pref[x - 1] : 0));
                break;
            default:
                std::scanf("%d", &t);

				for(int ptr = x; ptr <= y; ptr++)
					pn[ptr] = std::min(pn[ptr], t);

				for (int q = x; q < n; q++)
					pref[q] = pn[q] + (q > 0 ? pref[q - 1] : 0);
					
                tree.rebuild(pn);
			}
		}
	}
	return 0;
}
