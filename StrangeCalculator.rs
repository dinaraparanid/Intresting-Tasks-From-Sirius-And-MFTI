/*Маленькая девочка Лиза нашла странный автомат для счета. Он состоит из клеток, которые
соединены друг с другом проводками, концы которых помечены символами 􀀀 и +. В каждой клетке
автомата написано либо число, либо операция, либо переменная. В инструкции к автомату она
прочитала, что данные передаются по проводкам от клетки с минусом к клетке с плюсом. В этом
случае будем говорить, что клетка с плюсом зависит от клетки с минусом.
Работает устройство следующим образом:
 результатом вычисления в клетке, которая не помечена ни одним плюсом, является значение,
записанное в неё;
 для всех клеток устройства, сначала вычисляются значения в клетках, от которых зависит
результат вычисления в этой клетке, после чего выполняется операция последовательно для
всех входных данных;
 результат, полученный в клетке с номером 1, является итоговым.
Если в клетке записана операция, то результат ее вычисления зависит от результата не менее
двух других клеток. Если в клетке записана переменная или константа, то она не зависит от ре-
зультата других клеток. Гарантируется, что существует не более одной клетки с переменной и для
любой клетки с умножением существует не более одной цепочки зависимостей из клетки с перемен-
ной. Вычисление всегда завершается.
Лиза решила убедиться в корректности работы вычислителя. Для этого она написала набор
чисел — значений x. Для каждого из этих значений она хочет узнать результат, который должно
выдать устройство. Помогите ей с проверкой.
Формат входных данных
В первой строке входного файла записаны три числа N, M, и Q — количество клеток, количество
зависимостей и количество значений переменной (1 ⩽ N;M;Q ⩽ 105).
Во второй строке записаны N выражений в порядке, соответствующем номерам клеток, в кото-
рых эти выражения записаны:
 + означает, что результат в соответствующей клетке равен сумме значений от которых эта
клетка зависит;
  означает, что результат в соответствующей клетке равен произведению значений в клетках,
от которых данная клетка зависит;
 x означает, что в данной клетке записывается переменная;
 val означает, что в соответствующей клетке записана константа val (1 ⩽ val ⩽ 109 + 8).
В следующих M строках записано по два числа u и v — зависимость клетки v от значения в
клетке u (1 ⩽ u; v ⩽ N, u ̸= v).
В следующих Q строках записаны значения переменной x (0 ⩽ x ⩽ 109 + 8).
Формат выходных данных
В выходной файл выведите Q строк, в каждой из которых по одному числу — результат, по-
лученный на вычислителе для очередного значения x. Так как результат может быть большим,
выведите остаток от деления на 109 + 9.
Система оценки
Баллы за каждую подзадачу начисляются только в случае, если все тесты для этой подзадачи
и необходимых подзадач успешно пройдены.
Страница 5 из 10
I отборочный этап Всесибирской открытой олимпиады школьников по информатике 2020-2021
Новосибирск, 18 октября 2020 года
Подзадача Баллы Ограничения Необходимые
подзадачи
1 23 N;M ⩽ 105;Q ⩽ 100,
от каждой клетки зависит не более 1 клетки
2 24 N;M;Q ⩽ 105,
от каждой клетки зависит не более 1 клетки 1
3 11 N;M;Q ⩽ 105, нет клеток с выражением x
4 42 N;M;Q ⩽ 105 1, 2, 3

Примеры
input.txt output.txt
3 2 2
+ 3 x
2 1
3 1
2
3
5

6


5 6 1
+ + * x 3
2 1
3 1
4 2
4 3
3 2
5 3
2

14
*/

use std::io;

const DEL: u128 = 1000000009;

fn rec (act: &Vec<(usize, usize)>, moves: &Vec<String>, ind: usize, val: u128) -> u128 {
    return unsafe {
        match moves.get_unchecked(ind).as_str() {
            "x" => val,

            "+" => (rec(act, moves, act.get_unchecked(ind).0, val) +
                rec(act, moves, act.get_unchecked(ind).1, val)) % DEL,

            "*" => (rec(act, moves, act.get_unchecked(ind).0, val) *
                rec(act, moves, act.get_unchecked(ind).1, val)) % DEL,

            _ => moves.get_unchecked(ind).trim().parse::<u128>().unwrap(),
        }
    }
}

#[inline]
fn input_str() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input
}

fn main() {
    let input = input_str();
    let mut input_it = input.split_ascii_whitespace();

    let n = input_it.next().unwrap().parse::<usize>().unwrap();
    let m = input_it.next().unwrap().parse::<i32>().unwrap();
    let q = input_it.next().unwrap().parse::<i32>().unwrap();

    let moves = input_str().split_ascii_whitespace()
        .map(|x| x.to_string()).collect::<Vec<String>>();

    let mut act = vec![(usize::MAX, usize::MAX); n];

    for _m in 0..m {
        let input = input_str();
        let mut input_it = input.split_ascii_whitespace();

        let f = input_it.next().unwrap().parse::<usize>().unwrap();
        let s = input_it.next().unwrap().parse::<usize>().unwrap();

        unsafe {
            match act.get_unchecked(s - 1).0 {
                usize::MAX => act.get_unchecked_mut(s - 1).0 = f - 1,
                _ => act.get_unchecked_mut(s - 1).1 = f - 1,
            }
        }
    }

    if let 0 = q {
        println!("{}", rec(&act, &moves, 0, 0));
    } else {
        for _q in 0..q {
            println!("{}", rec(&act, &moves, 0, input_str().trim().parse::<u128>().unwrap()));
        }
    }
}
