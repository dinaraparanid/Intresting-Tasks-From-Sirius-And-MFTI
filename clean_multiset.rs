use std::io;

fn erase(mut vector: &mut [i32], count: &mut u128) {
    if vector.is_empty() {
        return
    }
    
    let mut ind: usize = 0;
    let mut min = std::i32::MAX;
        
    for i in 0..vector.len() {
        unsafe {
            if *vector.get_unchecked(i) < min {
                min = *vector.get_unchecked(i);   
                ind = i;
            }  
        }
    }
        
    for elem in vector {
        *elem -= min;
    }
    
    count += 1;
    
    erase(&vector[0..ind]);
    erase(&vector[ind..]);
}

fn main() {
    let mut n = String::new();
    io::stdin().read_line(&mut n).unwrap();
    let n = n.trim().parse::<i32>().unwrap();
    
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    
    let mut vector = Vec::with_capacity(n as usize);
    
    let mut input = input.split_whitespace();
    
    let mut vector = input.map(|x| x.parse::<i32>().unwrap()).collect::<Vec<i32>>();
    
    let mut count: u128 = 0;
    
    erase(&mut vector, count);
    
    println!("{}", count);
}
