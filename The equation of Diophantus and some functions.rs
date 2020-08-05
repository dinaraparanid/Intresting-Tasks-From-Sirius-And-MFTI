// Теория 2 модуля о теории чисел + решение диофантового уравнения 


use std::io;

fn input() -> i128 {
    let mut _s: String = String::new();
    io::stdin().read_line(&mut _s).expect("read_line");
    return _s.trim().parse().expect("convert")
}

fn binpow (a: i128, n: i128) -> i128 {
    if n == 0 {
        return 1
    }
    if n % 2 == 1 {
        return binpow(a, n - 1) * a
    } else {
        let b = binpow(a, n / 2);
        return b * b
    }
}

fn gcd(mut a: i128, mut b: i128) -> i128 {
    while b > 0 {
        a %= b;
        a += b;
        b = a - b;
        a -= b;
    }
    return a
}

fn gcd_ext(_a: i128, _b: i128, _x: &mut i128, _y: &mut i128) -> i128 {
    if _b == 0 {
        *_x = 1;
        *_y = 0;
        return _a
    }
    let _d = gcd_ext(_b, _a % _b, _x, _y);
    *_x -= (_a / _b) * *_y;
    *_x += *_y;
    *_y = *_x - *_y;
    *_x -= *_y;
    return _d
}

fn phi(mut _n: i128) -> i128 {
    let mut _res = _n;
    for _p in 2.._n {
        if _n % _p == 0 {
            _res -= _res / _p;
        }
        while _n % _p == 0 {
            _n /= _p;
        }
    }
    if _n > 1 {
        _res -= _res / _n;
    }
    return _res
}

fn main() {
    let mut _a = input(); // ввод каждый раз с новой строки
    let mut _b = input();
    let mut _c = input();
    let mut _x = 0;
    let mut _y = 0;
    let _d = gcd_ext(_a, _b, &mut _x, &mut _y);
    if _c % _d != 0 {
        print!("Impossible");
    } else {
        let mut _t = 0;
        let _yy = _y;
        let _xx = _x;
        _x = _c / _d * _xx;
        _y = _c / _d * _yy;
        if _x > 0 {
            while _x > 0 {
                _t -= 1;
                _x = (_c / _d) * _xx + _t * (_b / _d);
                _y = (_c / _d) * _yy - _t * (_a / _d);
            }
            if _x != 0 {
                _t += 1;
                _x = (_c / _d) * _xx + _t * (_b / _d);
                _y = (_c / _d) * _yy - _t * (_a / _d);
            }
        } else {
            while _x < 0 {
                _t += 1;
                _x = (_c / _d) * _xx + _t * (_b / _d);
                _y = (_c / _d) * _yy - _t * (_a / _d);
            }
        }
        print!("{} {}", _x, _y);
    }
}