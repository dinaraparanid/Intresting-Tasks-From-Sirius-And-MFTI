/*
Суперчисла
Суперчислом называется число, являющееся суммой двух простых чисел из диапазона [2…B]. Требуется найти все суперчисла из заданного диапазона [A…B].
Примеры
Ввод 3 10
Вывод
4
5
6
7
8
9
10
*/

use std::io;

fn input() -> i32 {
    let mut _s: String = String::new();
    io::stdin().read_line(&mut _s).expect("read_line");
    return _s.trim().parse().expect("convert");
}

fn main() {
    let mut _a = input();
    let mut _b = input();
    let mut _prime = vec![];
    _prime.resize((_b + 1) as usize, 1);
    let mut _iz = vec![];
    for _i in 2.._b + 1 {
        if _prime[_i as usize] == 1 {
            _iz.push(_i);
        }
        if _prime[_i as usize] == 0 || _i as i128 * 1 as i128 * _i as i128 > _b as i128 {
            continue;
        }
        for _j in (_i * _i.._b + 1).step_by(_i as usize) {
            _prime[_j as usize] = 0;
        }
    }
    let mut _size = 0;
    let mut _am = 0;
    let _izs = _iz.len();
    for _i in (1.._izs + 1).rev() {
        _size += _i;
    }
    let mut _ans = vec![];
    _ans.resize(_size, 0);
    for _i in 0.._izs {
        for _j in _i.._izs {
            _ans[_am as usize] = _iz[_i as usize] + _iz[_j as usize];
            _am += 1;
        }
    }
    _ans.sort();
    let mut _print = false;
    let mut _it = 0;
    while !_print {
        if _ans[_it as usize] >= _a {
            _print = true;
        } else {
            _it += 1;
        }
    }
    println!("{}", _ans[_it as usize]);
    for _i in _it + 1.._size {
        if _ans[_i as usize] != _ans[(_i - 1) as usize] && _ans[_i as usize] >= _a && _ans[_i as usize] <= _b {
            println!("{}", _ans[_i as usize]);
        }
    }
}