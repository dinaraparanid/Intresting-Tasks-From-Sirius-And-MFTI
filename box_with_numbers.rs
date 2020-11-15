/*B. Коробка с числами
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Вам дана прямоугольная сетка с n строками и m столбцами. В ячейке, расположенной на i-й строке сверху и j-м столбце слева, записано значение aij.

Вы можете выполнить следующую операцию любое количество раз (возможно, ноль):

Выберите любые две соседние ячейки и умножьте значения в них на −1. Две ячейки называются соседними, если они имеют общую сторону.
Обратите внимание, что одну и ту же ячейку можно использовать несколько раз при различных операциях.

Вас интересует X, сумма всех чисел в сетке.

Какое максимально возможное X вы можете получить с помощью данных операций?

Входные данные
Каждый тест содержит несколько наборов входных данных. В первой строке указано количество наборов входных данных t (1≤t≤100). Описание наборов входных данных приведено ниже.

Первая строка каждого набора входных данных содержит два целых числа n,m (2≤n, m≤10).

Каждая из следующих n строк содержит по m целых чисел, j-й элемент в i-й строке  — aij (−100≤aij≤100).

Выходные данные
Для каждого набора входных данных выведите одно целое X  — максимально возможную сумму всех значений в сетке после применения операции столько раз, сколько вам нужно.

Пример
входные данныеСкопировать
2
2 2
-1 1
1 1
3 4
0 -1 -2 -3
-1 -2 -3 -4
-2 -3 -4 -5
выходные данныеСкопировать
2
30
Примечание
В первом наборе входных данных всегда будет как минимум одна −1, так что ответ равен 2.

Во втором наборе входных данных можно шесть раз использовать операцию для элементов, соседних по горизонтали, и сделать все числа неотрицательными. Так что ответ: 2×1+3×2+3×3+2×4+1×5=30.*/

use std::fmt::Debug;
use std::io;
use std::num::ParseIntError;
use std::str::FromStr;

#[inline]
fn input<T: FromStr<Err = ParseIntError> + Debug>() -> T {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().parse().unwrap()
}

#[inline]
fn input_vec<T: FromStr<Err = ParseIntError> + Debug>() -> Vec<T> {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input
        .split_ascii_whitespace()
        .map(|x| x.parse::<T>().unwrap())
        .collect()
}

#[inline]
fn input_pair<T: FromStr<Err = ParseIntError> + Debug>() -> (T, T) {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();
    (
        input.next().unwrap().parse().unwrap(),
        input.next().unwrap().parse().unwrap(),
    )
}

fn main() {
    let t = input::<i32>();

    for _ in 0..t {
        let (n, m) = input_pair::<usize>();
        let mut vec = vec![vec![0; m]; n];

        for i in &mut vec {
            *i = input_vec::<i32>();
        }

        let mut map = Vec::<(i32, usize, usize)>::new();

        for i in 0..n {
            for q in 0..m {
                unsafe {
                    if *vec.get_unchecked(i).get_unchecked(q) <= 0 {
                        map.push((*vec.get_unchecked(i).get_unchecked(q), i, q));
                    }
                }
            }
        }

        map.sort_by(|x, y| (x.0).partial_cmp(&y.0).unwrap());

        let mut sum = 0_i128;

        for i in 0..n {
            for q in 0..m {
                unsafe {
                    sum += (*vec.get_unchecked(i).get_unchecked(q)).abs() as i128;
                }
            }
        }

        if map.len() % 2 != 0 {
            let mut min = 101;

            for i in 0..n {
                for q in 0..m {
                    unsafe {
                        if min > (*vec.get_unchecked(i).get_unchecked(q)).abs() {
                            min = (*vec.get_unchecked(i).get_unchecked(q)).abs();
                        }
                    }
                }
            }

            sum -= min as i128 * 2;
        }

        println!("{}", sum);
    }
}
