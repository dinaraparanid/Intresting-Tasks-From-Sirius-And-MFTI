# Даётся длина строки и сама строка, состоящая из цифр.
# Задача - подсчитать кол-во палиндромов, полученных путёв выбора
# Т.к. ответ может быть большой, то вывести по модулю 1е9

n = int(input())
de = 10**9

nums = list(map(int, input().split()))
memo = [[0] * n for i in range(n)]

for q in range(n):
	memo[q][q] = 1
	
for r in range(1,n):
	i = 0
	q = r
	
	while q < n:
		memo[i][q] = (memo[i + 1][q] + memo[i][q - 1] - memo[i + 1][q - 1]) % de
		
		if nums[i] == nums[q]:
			memo[i][q] = (memo[i][q] % de + memo[i + 1][q - 1] % de + 1) % de;
		
		i += 1
		q += 1

print(memo[0][n - 1] % de)
