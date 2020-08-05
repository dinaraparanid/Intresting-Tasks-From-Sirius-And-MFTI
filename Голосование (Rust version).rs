use std::collections::BTreeMap;
use std::io;
use std::str::SplitWhitespace;

fn main() {
    let mut n: String = String::new();
    io::stdin().read_line(&mut n).unwrap();
    let n: i128 = n.trim().parse().unwrap();
    let mut amount: BTreeMap<String, i128> = BTreeMap::new(); // кол-во голосующих от штатов
    for _i in 0..n {
        let mut input: String = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let mut it_input: SplitWhitespace = input.split_whitespace();
        let state: String = it_input.next().unwrap().to_string();
        let voices: i128 = it_input.next().unwrap().parse().unwrap();
        amount.insert(state, voices);
    } // заполнили колвом голосов
    let mut m: String = String::new();
    io::stdin().read_line(&mut m).unwrap();
    let m: i128 = m.trim().parse().unwrap();
    let mut voice: BTreeMap<String, BTreeMap<String, i128>> = BTreeMap::new(); // голосование в штате
    let mut victory: BTreeMap<String, i128> = BTreeMap::new();
    for _i in 0..m {
        let mut input: String = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let mut it_input: SplitWhitespace = input.split_whitespace();
        let state: String = it_input.next().unwrap().to_string();
        let guy: String = it_input.next().unwrap().to_string();
        if !victory.contains_key(&guy) {
            victory.insert(guy.clone(), 0);
        }
        if !voice.contains_key(&state) {
            let mut ins: BTreeMap<String, i128> = BTreeMap::new();
            ins.insert(guy, 1);
            voice.insert(state, ins);
        } else {
            if !voice[&state].contains_key(&guy) {
                voice.get_mut(&state).unwrap().insert(guy, 1);
            } else {
                *voice.get_mut(&state).unwrap().get_mut(&guy).unwrap() += 1;
            }
        }
    } // голосование в каждом штате
    let mut guys: BTreeMap<String, String> = BTreeMap::new();
    // победитель в штате (штат, имя)
    for it in voice.iter() {
        let mut max: (String, i128) = ("".to_string(), -1);
        for its in it.1.iter() {
            if its.1 > &max.1 {
                max.0 = its.0.to_string();
                max.1 = *its.1;
            }
        }
        guys.insert(it.0.to_string(), max.0);
    }
    for guy in guys.iter() {
        *victory.get_mut(guy.1).unwrap() += *amount.get_mut(guy.0).unwrap();
    }
    let mut print: Vec<(String, i128)> = Vec::with_capacity(victory.len());
    print.resize(victory.len(), ("".to_string(), 0));
    // сортировка по значению
    let mut ind: usize = 0;
    for it in victory {
        print[ind] = it;
        ind += 1;
    }
    print.sort();
    let mut start: usize = 0;
    let mut finish: usize = 0;
    for mut i in 0..print.len() - 1 {
        if print[i].1 != print[i + 1].1 {
            start += 1;
            finish += 1;
        } else {
            while i < print.len() - 1 && print[i].1 == print[i + 1].1 {
                finish += 1;
                i += 1;
            }
            &mut print[start..finish].reverse();
            finish += 1;
            start = finish;
        }
    } // сортировка имён
    for i in print {
        println!("{} {}", i.0, i.1);
    }
}