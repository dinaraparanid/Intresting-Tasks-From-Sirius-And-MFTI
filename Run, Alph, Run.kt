/*
Ограничение по времени:2 секунды
Ограничение по памяти:256 мегабайт
Прямо сейчас Альфу снится кошмар. В нем он бежит по дороге с препятствиями, на которой,ко всему прочему, разбросаны монеты.
Дорога представляет из себя таблицу n×3, в клетках которой либо ничего нет, либо находитсястена, либо монета.
Альф бежит вдоль стороны длиной n. Начинает он бежать из первой строки (то есть у него есть три варианта начала,
он может выбрать любой из них) и бежит до тех пор, пока не врежется в стену, либо не пробежит дорогу целиком (не окажется в строчке n).
Пусть сейчас Альф стоит в cтроке x и столбце y (x;y), тогда он может попасть в три возможныеклетки:(x + 1;y−1),(x + 1;y),(x + 1;y+ 1),
если конечно новая клетка не выходит за пределы дороги, и в ней не находится стена. Так как все обитатели планеты Мелмак умеют контролироватьсвои сны,
Альф смог получить карту дороги. Теперь он хочет узнать, какое наибольшее количество монет можно собрать к концу забега.Так как контроль сна отнимает 
у Альфа много сил, он просит вас написать программу, которая по карте сможет определить наибольшее количество монет, которое можно собрать за один забег.
Формат входных данных В первой строке входного файла задано числоn(1<=n<=10e4)  количество строк в таблице.
В следующих n строках дано по три символа, характеризующие данную строку таблицы: ., если клетка пустая, C, если в этой клетке монета, и W, если стена.
Если в первой строке во всех клетках находятся стены, Альф заканчивает забег сразу.
Формат выходных данных В выходной файл выведите одно число наибольшее количество монеток, которые можно собрать.
Примеры стандартный ввод
стандартный вывод
5
W.W
C.C
WW.
CC.
CWW

3


4
W.W
CWC
W.W
CWW

2
*/

import kotlin.math.max
 
const val INF = (-2e9).toInt()
 
fun dfs(dp: MutableList<MutableList<Int>>, matrix: MutableList<List<Char>>, q: Int, i: Int = 0, _sum: Int = 0): Int {
    if (dp[i][q] != INF)
        return dp[i][q]
 
    if (i == matrix.size - 1) {
        return if (matrix[i][q] == 'C') 1 else 0
    }
 
    if (q == 0) {
        dp[i][q] = max(
                if (matrix[i + 1][q] != 'W') dfs(dp, matrix, q, i + 1, dp[i][q]) else max(dp[i][q], 0),
                if (matrix[i + 1][q + 1] != 'W') dfs(dp, matrix, q + 1, i + 1, dp[i][q]) else max(dp[i][q], 0)
        )
 
        dp[i][q] += if (matrix[i][q] == 'C') 1 else 0
        return dp[i][q]
    }
 
    if (q == 2) {
        dp[i][q] = max(
                if (matrix[i + 1][q] != 'W') dfs(dp, matrix, q, i + 1, dp[i][q]) else max(dp[i][q], 0),
                if (matrix[i + 1][q - 1] != 'W') dfs(dp, matrix, q - 1, i + 1, dp[i][q]) else max(dp[i][q], 0)
        )
 
        dp[i][q] += if (matrix[i][q] == 'C') 1 else 0
        return dp[i][q]
    }
 
    dp[i][q] = max(
            if (matrix[i + 1][q] != 'W') dfs(dp, matrix, q, i + 1, dp[i][q]) else max(dp[i][q], 0),
            max(
                    if (matrix[i + 1][q - 1] != 'W') dfs(dp, matrix, q - 1, i + 1, dp[i][q]) else max(dp[i][q], 0),
                    if (matrix[i + 1][q + 1] != 'W') dfs(dp, matrix, q + 1, i + 1, dp[i][q]) else max(dp[i][q], 0)
            )
    )
 
    dp[i][q] += if (matrix[i][q] == 'C') 1 else 0
    return dp[i][q]
}
 
fun main() {
    val n = (readLine() ?: return).toInt()
    val matrix = MutableList(n) { List(3) { ' ' } }
    val dp = MutableList(n) { MutableList(3) { INF } }
 
    for (i in 0 until n)
        matrix[i] = (readLine() ?: return).toList()
 
    print(max(
            if (matrix[0][0] != 'W') dfs(dp, matrix, 0) else 0,
            max(
                    if (matrix[0][1] != 'W') dfs(dp, matrix, 1) else 0,
                    if (matrix[0][2] != 'W') dfs(dp, matrix, 2) else 0
            )
    ))
}
