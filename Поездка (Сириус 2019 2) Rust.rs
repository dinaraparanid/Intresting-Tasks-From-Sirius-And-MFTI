/*В 2029 году три финала Всероссийской олимпиады — по химии, информатике и физкультуре — проводятся в Самаре. Из Саратова прошло много участников по каждому из этих предметов, и все они планируют ехать в Самару на поезде. Руководитель сборной по химии уже купил билеты для своих подопечных. Руководитель сборной по информатике как раз сейчас планирует этим заняться. Но программисты — странные люди, у которых есть много запросов к купленным местам. Например, они категорически не хотят ехать в одном вагоне со спортсменами (участниками сборной по физкультуре), а также со всеми другими людьми, не прошедшими на всерос (то есть, из всех возможных людей, они готовы терпеть только всероссников по химии).

К счастью, пока кроме химиков ещё никто не успел купить билеты на поезд, так что всё, что нужно обеспечить руководителю, это чтобы после покупки билетов, в вагонах, в которых поедут участники сборной по информатике не осталось свободных мест (тогда там точно не поедут посторонние).

Но у руководителя есть и свои ограничения — он хочет, чтобы вагонов, в которых поедут его подопечные, было как можно меньше и они шли подряд (при этом допускается, чтобы между ними были целиком занятые вагоны).

Помогите руководителю сборной выбрать, в каких вагонах информатики поедут на олимпиаду, или определите, что это невозможно.

Входные данные
В первой строке дано два целых числа n и k (1≤n≤105,1≤k≤109) — число вагонов и участников сборной соответственно.

Во второй строке даны n целых чисел ai (0≤ai≤109) — количество свободных мест в вагонах.

Гарантируется, что суммарное число свободных мест в поезде не превосходит 109.

Выходные данные
Выведите два целых числа — номера первого и последнего вагона, в которых поедут участники сборной.

Если же купить билеты, соблюдая все требования, невозможно, выведите -1.

Система оценки


Примеры
входные данные
7 5
1 2 3 4 2 1 2
выходные данные
2 3
входные данные
5 3
1 0 2 10 10
выходные данные
1 3
*/


use std::collections::VecDeque;
use std::io;
use std::str::SplitWhitespace;

fn main() {
    let mut amount: String = String::new();
    io::stdin().read_line(&mut amount).unwrap();

    let mut it_am: SplitWhitespace = amount.split_whitespace();
    let n: usize = it_am.next().unwrap().parse().unwrap();
    let k: u32 = it_am.next().unwrap().parse().unwrap();

    let mut pn_s: String = String::new();
    io::stdin().read_line(&mut pn_s).unwrap();

    let mut pn: Vec<u32> = Vec::with_capacity(n);

    let mut it_pns: SplitWhitespace = pn_s.split_whitespace();

    let mut c = 0;
    loop {
        pn.push(it_pns.next().unwrap().parse().unwrap());
        c += 1;
        if c == n {
            break;
        }
    }

    let mut sum: u32 = 0;
    let mut que: VecDeque<usize> = VecDeque::new();
    let mut ptr: usize = 0;

    let mut best_s: usize = 0;
    let mut best_f: usize = 0;
    let mut best_l = std::usize::MAX;

    loop {
        if sum < k {
            unsafe {
                sum += *pn.get_unchecked(ptr);
            }
            que.push_back(ptr);
            ptr += 1;
        } else if sum > k {
            unsafe {
                sum -= *pn.get_unchecked(*que.front().unwrap());
            }
            que.pop_front();
        } else {
            if *que.back().unwrap() - *que.front().unwrap() < best_l {
                best_l = *que.back().unwrap() - *que.front().unwrap();
                best_s = *que.front().unwrap();
                best_f = *que.back().unwrap();
            }

            unsafe {
                sum -= *pn.get_unchecked(*que.front().unwrap());
            }
            que.pop_front();
        }
        if ptr >= pn.len() {
            break;
        }
    }

    if sum > k {
        loop {
            unsafe {
                sum -= *pn.get_unchecked(*que.front().unwrap());
            }
            que.pop_front();

            if sum <= k {
                break;
            }
        }
    }

    if sum == k {
        if *que.back().unwrap() - *que.front().unwrap() < best_l {
            best_l = *que.back().unwrap() - *que.front().unwrap();
            best_s = *que.front().unwrap();
            best_f = *que.back().unwrap();
        }
    }

    if best_l != n + 1 {
        print!("{} {}", best_s + 1, best_f + 1);
    } else {
        print!("-1");
    }
}