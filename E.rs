/*
Для пассажиров кольцевой железнодорожной линии, построенной в столице Байтландии, существует следующая система абонементных билетов. Заплатив ai байтландских тугриков, пассажир получает право проезда от станции 0 до станции i (и только до неё). Таким образом, право проезда на две станции i и j даёт абонементный билет стоимостью ai+aj. Так как, кроме станции 0, на кольцевой линии находятся ещё n станций, то всего существует 2^n различных абонементов (включая и бесплатный абонемент со станции 0 до самой себя), отличающиеся множеством станций, до которых они дают проезд.

Вам дана стоимость каждого из 2n абонементов. Требуется восстановить ai или сообщить, что при передаче списка стоимостей абонементов произошла ошибка и ни при каких ai указанные стоимости не могут быть сформированы.

Формат ввода
Первая строка содержит одно целое число n (1 ≤ N ≤ 18) — количество станций (кроме станции 0), находящихся на линии. Каждая их последующих 2n строк содержит одно целое число — стоимость очередного абонемента (0 ≤ p ≤ 228).

Формат вывода
Выведите n целых чисел в неубывающем порядке — значения ai. Если вариантов несколько, выведите любой.

Если решения нет, выведите текст “impossible”.
*/

use std::io;

fn main() {
    let mut pn: Vec<u32> = Vec::with_capacity(229);
    for _i in 0..229 {
        pn.push(0);
    }

    let mut n: String = String::new();
    io::stdin().read_line(&mut n).unwrap();
    let n: u32 = n.trim().parse().unwrap();

    let mut max: i32 = -1;
    for _i in 0..2_u32.pow(n) {
        let mut x: String = String::new();
        io::stdin().read_line(&mut x).unwrap();
        let x: usize = x.trim().parse().unwrap();
        if x as i32 > max {
            max = x as i32;
        }
        unsafe {
            *pn.get_unchecked_mut(x) += 1;
        }
    }

    for _i in max as usize + 1..pn.len() {
        pn.remove(max as usize + 1);
    }

    let mut correct: bool = true;
    unsafe {
        if *pn.get_unchecked(0) == 0 {
            correct = false;
        } else {
            *pn.get_unchecked_mut(0) -= 1;
        }
    }

    if n == 1 {
        if !correct {
            print!("impossible");
        } else {
            unsafe {
                for i in 0..pn.len() {
                    if *pn.get_unchecked(i) > 0 {
                        print!("{}", i);
                        break;
                    }
                }
            }
        }
    } else {
        if correct {
            let mut ans: Vec<u32> = Vec::with_capacity(n as usize);
            let mut sums: Vec<u32> = Vec::with_capacity(2_usize.pow(n));

            let mut ptr: usize = 0;
            let mut v1: u32 = 0;
            let mut v2: u32 = 0;

            unsafe {
                while *pn.get_unchecked(ptr) == 0 {
                    ptr += 1;
                }
                v1 = ptr as u32;
                *pn.get_unchecked_mut(ptr) -= 1;
                while *pn.get_unchecked(ptr) == 0 {
                    ptr += 1;
                }
                v2 = ptr as u32;
                *pn.get_unchecked_mut(ptr) -= 1;
            }

            ans.push(v1);
            ans.push(v2);

            sums.push(v1 + v2);
            sums.push(v1);
            sums.push(v2);
            unsafe {
                if v1 + v2 >= pn.len() as u32 || *pn.get_unchecked(v1 as usize + v2 as usize) == 0 {
                    correct = false;
                } else {
                    *pn.get_unchecked_mut(v1 as usize + v2 as usize) -= 1;
                }
            }

            if correct {
                for i in ptr..pn.len() {
                    if !correct {
                        break;
                    }
                    unsafe {
                        if *pn.get_unchecked(i) > 0 {
                            while *pn.get_unchecked(i) > 0 {
                                for q in 0..sums.len() {
                                    let b: u32;
                                    {
                                        b = *sums.get_unchecked(q);
                                    }
                                    sums.push(b + i as u32);
                                    if b as usize + i >= pn.len()
                                        || *pn.get_unchecked_mut(b as usize + i) == 0
                                    {
                                        correct = false;
                                        break;
                                    } else {
                                        *pn.get_unchecked_mut(b as usize + i) -= 1;
                                    }
                                }
                                if correct {
                                    *pn.get_unchecked_mut(i) -= 1;
                                    ans.push(i as u32);
                                    sums.push(i as u32);
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            drop(pn);
            drop(sums);

            for i in ans {
                println!("{}", i);
            }
        } else {
            println!("impossible");
        }
    }
}