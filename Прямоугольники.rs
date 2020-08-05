/*Прямоугольники
Дана последовательность N прямоугольников различной ширины и высоты (wi,hi). Прямоугольники расположены, начиная с точки (0,0), вправо на оси OX вплотную друг за другом. Требуется найти M — площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой фигуры.

Формат входных данных

В первой строке задано число N (1≤N≤105). Далее идут N строк. В каждой строке содержатся два числа: ширина и высота i-го прямоугольника (1<wi≤3⋅104, 0≤hi≤3⋅104).

Формат выходных данных

Выведите искомое число M.

Примеры
Ввод
Вывод

3
4 3
2 1
2 5

12


3
4 3
2 1
3 5

15
*/



// stack.rs

pub mod stack {
	
	/*#-#-#-#-#-#-Реализация стека-#-#-#-#-#-#-#*/
	
	#[derive(Clone, PartialEq, Debug)]
	pub struct Stack<T> {
		container: Vec<T>,
	}
	
	impl<T> Stack<T> {
		
		// Создаём новый стек
		
		pub fn new() -> Self {
			Stack { container: vec![] }
		}
		
		// Добавление элемента
		// в конец стека
		
		pub fn push(&mut self, value: T) {
			self.container.push(value);
		}
		
		// Удаление элемента из стека
		// В случае успеха возвращает ссылку
		// на удалённый элемент
		// иначе None
		
		pub fn pop(&mut self) {
			self.container.pop();
		}
		
		// Очистка стека
		
		pub fn clear(&mut self) {
			self.container.clear();
		}
		
		// Функция возвращает указатель
		// на последний элемент стека
		
		pub fn top(&mut self) -> Option<&T> {
			return self.container.last()
		}
		
		// функция проверки стека на пустоту
		
		pub fn is_empty(&self) -> bool {
			self.container.is_empty()
		}
	}
}


// main.rs

mod stack;
use std::io;
use crate::stack::stack::Stack;

fn main() {
    // Считываем кол-во данных
    let mut n = String::new();
    io::stdin().read_line(&mut n).unwrap();
    let n: usize = n.trim().parse().unwrap();
    
    // Заводим вектор под данные
    let mut pn = Vec::with_capacity(n + 2);
    pn.resize(n + 2, (0, 0));
    
    // Считываем данные
    for i in 1..n + 1 {
        let mut elem = String::new();
        io::stdin().read_line(&mut elem).unwrap();
        
        let mut it_elem = elem.split_whitespace();
        pn[i].1 = it_elem.next().unwrap().parse().unwrap();
        pn[i].0 = it_elem.next().unwrap().parse().unwrap();
    }
    
    // Вектор, хранящий индекс ближайшего элемента
    // справа, меньше текущего
    let mut ans_r = Vec::with_capacity(n);
    ans_r.resize(n, 0);
    
    // Храним всё в стеке. Когда встречаем
    // элемент, меньше нашего, то пишем ответы,
    // удаляем элементы из стека, которые
    // больше текущего, а затем добавляем в стек
    
    let mut st_r = Stack::new();
    st_r.push(0);
    
    //Делаем всё вышесказанное
    
    for i in 1..n + 2 {
        
        if pn[i].0 >= pn[*st_r.top().unwrap()].0 {
            st_r.push(i);
            
        } else {
            
            while pn[i].0 < pn[*st_r.top().unwrap() as usize].0 {
                ans_r[*st_r.top().unwrap() as usize - 1] = if i == n + 1 { n } else { i - 1 };
                st_r.pop();
            }
            
            st_r.push(i);
        }
    }
    
    // Делаем всё тоже, но уже идём влево
    
    let mut ans_l: Vec<i32> = Vec::with_capacity(n);
    ans_l.resize(n, 0);
    
    let mut st_l: Stack<i32> = Stack::new();
    st_l.push(n as i32 + 1);
    
    // for заменить на while оказалось проще
    // нежели долбаться с for-ом
    
    let mut g = n as i32;
    while g >= 0 {
        if pn[g as usize].0 >= pn[*st_l.top().unwrap() as usize].0 {
            st_l.push(g);
        } else {
    
            while pn[g as usize].0 < pn[*st_l.top().unwrap() as usize].0 {
                ans_l[*st_l.top().unwrap() as usize - 1] = if g == 0 { -1 } else { g - 1 };
                st_l.pop();
            }
            
            st_l.push(g);
        }
        g -= 1;
    }
    
    // Находим максимальную площадь
    
    let mut max_s = 0;
    
    // Заранее посчитаем всю ширину с помощью
    // массива префиксных сумм
    // чтобы не считать каждый раз в цикле
    
    let mut ph = Vec::with_capacity(n + 1);
    ph.resize(n + 1, 0_usize);
    
    for i in 1..n + 1 {
        ph[i] = pn[i].1 + ph[i - 1];
    }
    
    // Находим наибольшую площадь
    
    for i in 0..n {
        let s = (pn[i + 1].0) as i128 * ((ph[ans_r[i]]) as i128 - (ph[(ans_l[i] + 1) as usize]) as i128);
        max_s = if s > max_s  { s } else { max_s };
    }
    
    print!("{}", max_s);
}