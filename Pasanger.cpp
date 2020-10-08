/*С целью уменьшения нагрузки на станции метро в столице Байтландии в часы пик мэрия 
приняла решение об изменении сети наземных маршрутов. Эксперимент проводился на
одной линии метро, соединяющей n станций. Станции занумерованы последовательными
целыми числами от 1 до n.
Также проводились наблюдения относительно значений максимального и суммарного 
пассажиропотока на участках. В рамках этих наблюдений отмечались следующие события:

o x,y,t — для станций с номерами от x до y значение пассажиропотока ai после 
модификации наземных маршрутов стало равным min(ai,t).

m x,y — требуется найти максимальный пассажиропоток на станциях с номерами от x до y включительно.

s x,y — требуется найти суммарный пассажиропоток (то есть сумму всех ai) на 
станциях с номерами от x до y включительно.
Ваша задача — написать программу, обрабатывающие эти события в хронологическом порядке.

Пример
Ввод	Вывод
1 - кол-во тестов
5 5
2 3 4 5 6
m 1 5
s 1 5
o 3 5 4
m 1 5
s 1 5
6
20
4
17*/

#include <iostream>
#include <algorithm>
#include <vector>

enum STOrder
{
	MAX,
	MIN
};

template <typename T>
class SegmentTree
{
 private:
	size_t last_; // размер
	std::vector<T> builder_; // то, где поддерживаем rmq
	std::vector<T> constructor_; // первоначальный вектор
	STOrder order_;

	static inline T left(T _p) { return _p << 1; } // левая ветвь
	static inline T right(T _p) { return (_p << 1) + 1; }  // правая ветвь

	/**
	Построение дерева отрезков (сегментов).
	@param _p - текущее значение,
	@param _l - текущий индекс влево,
	@param _r - текущий индекс вправо
	*/

	void build (T _p, size_t _l, size_t _r)
	{
		if (_l == _r)
			builder_[_p] = _l; // дошли до листа
		else
		{
			build(left(_p), _l, (_l + _r) / 2); // строим левую ветвь
			build(right(_p), (_l + _r) / 2 + 1, _r); // строим правую ветвь

			// считаем rmq для права и лева
			const T p1 = builder_[left(_p)];
			const T p2 = builder_[right(_p)];

			// выбираем лучший результат
			if (order_ == MAX)
				builder_[_p] = (constructor_[p1] >= constructor_[p2] ? p1 : p2);
			else
				builder_[_p] = (constructor_[p1] <= constructor_[p2] ? p1 : p2);
		}
	}

	/**
	Нахождение rmq (range maximum query).
	@param _p - текущее значение,
	@param _l - текущий индекс влево,
	@param _r - текущий индекс вправо,
	@return rmq(_i, _j) в ЧАСТИ дерева
	*/

	T rmq (T _p, size_t _l, size_t _r, size_t _i, size_t _j)
	{
		if (_i > _r || _j < _l)  // если вышли за границу
			return -1;

		else if (_l >= _i && _r <= _j) // если попали
			return builder_[_p];

		// считаем rmq справа и слева
		const T p1 = rmq(left(_p), _l, (_l + _r) / 2, _i, _j);
		const T p2 = rmq(right(_p), (_l + _r) / 2 + 1, _r, _i, _j);

		if (p1 == -1) return p2;
		if (p2 == -1) return p1;

		// выбираем лучший результат
		if (order_ == MAX)
			return (constructor_[p1] >= constructor_[p2] ? p1 : p2);
		else
			return (constructor_[p1] <= constructor_[p2] ? p1 : p2);
	}

 public:

	/**
	Конструктор для дерева отрезков.
	@param _vec - вектор, для которого нужно найти rmq
	*/

	explicit SegmentTree(const std::vector<T>& _vec, STOrder _order)
	{
		constructor_ = _vec;
		last_ = _vec.size();
		order_ = _order;

		builder_.assign(4 * last_, 0);
		build(1, 0, last_ - 1);
	}

	/**
	Перестройка дерева.
	@param _vec - новый вектор
	*/

	inline void rebuild (const std::vector<T>& _vec)
	{
		constructor_ = _vec;
		std::for_each(builder_.begin(), builder_.end(), [](T& _elem) { _elem = 0; });
		build(1, 0, last_ - 1);
	}

	inline T rmq (size_t _i, size_t _j) { return rmq(1, 0, last_ - 1, _i, _j); } // перегрузка для нахождения
	// rmq(_i, _j) для всего дерева
};

int main()
{
	int tests = 0;
	std::scanf("%d", &tests);

	while (tests--)
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

		SegmentTree<int> tree(pn, MAX);

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

				for (int ptr = x; ptr <= y; ptr++)
					pn[ptr] = std::min(pn[ptr], t);

				for (int q = x; q < n; q++)
					pref[q] = pn[q] + (q > 0 ? pref[q - 1] : 0);

				tree.rebuild(pn);
			}
		}
	}
	return 0;
}
