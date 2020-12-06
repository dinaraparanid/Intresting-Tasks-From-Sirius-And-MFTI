/*
В классе n (2 <= n <= 10e5) человек. Есть один, который пришёл из другого класса. Он садится на некое место. Коренные ученики по-очереди садятся либо на свое место
(если он первый, то сядет на первое место), либо на aj из свободных. Например, если свободны места 2, 4, 7, aj = 2, то студент сядет на 4-е место. Есть староста,
который заходит последним и должен всегда сесть на своё n-ое место. Нужно подсчитать, сколько мест, на которых может сесть пришелец так, чтобы староста сел на своё

Примеры
стандартный ввод стандартный вывод
3
1 2

3


3
2 2

2
*/
use std::fmt::Debug;
use std::io;
use std::iter::FromIterator;
use std::num::ParseIntError;
use std::str::{FromStr, SplitWhitespace};

#[inline]
#[allow(dead_code)]
fn input<T: FromStr<Err = ParseIntError> + Debug>() -> T {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().parse().unwrap()
}

#[inline]
#[allow(dead_code)]
fn input_container<T, C>() -> C
where
    T: FromStr<Err = ParseIntError> + Debug,
    C: FromIterator<T>,
{
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input
        .split_ascii_whitespace()
        .map(|x| x.parse::<T>().unwrap())
        .collect::<C>()
}

#[inline]
#[allow(dead_code)]
fn input_pair<F, S>() -> (F, S)
where
    F: FromStr<Err = ParseIntError> + Debug,
    S: FromStr<Err = ParseIntError> + Debug,
{
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let mut input = input.split_whitespace();
    (
        input.next().unwrap().parse().unwrap(),
        input.next().unwrap().parse().unwrap(),
    )
}

#[inline]
#[allow(dead_code)]
fn input_it(mut input: &mut String) -> SplitWhitespace<'_> {
    io::stdin().read_line(&mut input).unwrap();
    input.split_whitespace()
}

fn main() {
    let n = input::<usize>();
    let choice = input_container::<usize, Vec<_>>();
    let mut dp = vec![false; n + 1];

    let mut ans = 1;

    unsafe {
        *dp.get_unchecked_mut(n) = true;

        *dp.get_unchecked_mut(n - 2) = match *choice.get_unchecked(n - 2) {
            1 => false,
            _ => true,
        };

        if *dp.get_unchecked_mut(n - 2) {
            ans += 1;
        }
        
        for i in (0..n - 2).rev() { // выбор мест за пидораса
            if i != n - 1 || i != n - 2 { // анти-босс
                if *dp.get_unchecked(i + *choice.get_unchecked(i)) {
                    *dp.get_unchecked_mut(i) = true;
                    ans += 1;
                }
            }
        }
    }

    print!("{}", ans);
}
