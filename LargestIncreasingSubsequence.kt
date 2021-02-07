// Найти наибольшую возрастающую подпоследовательность (НЕ ПОДОТРЕЗОК)

const val INF = 2e9.toInt()
 
fun main() {
    readLine()
 
    val arr = readLine()!!.split(' ').map { it.toInt() }.toIntArray()
    val dp = IntArray(arr.size + 1) { INF } // последнее число
    val pos = IntArray(arr.size + 1) // индекс
    val prev = IntArray(arr.size) // предыдущий
    var len = 0
 
    dp[0] = -INF; pos[0] = -1
 
    arr.forEachIndexed { ind, x ->
        val bs = dp.binarySearch(x) 
        val q = if (bs < 0) -(bs + 1) else bs // костыль джавы
 
        if (dp[q - 1] < x && x < dp[q]) {
            dp[q] = x
            pos[q] = ind
            prev[ind] = pos[q - 1]
            len = maxOf(len, q)
        }
    }
 
    val ans = mutableListOf<Int>()
    var p = pos[len]
 
    while (p != -1) {
        ans.add(arr[p])
        p = prev[p]
    }
 
    println(ans.size)
    ans.asReversed().forEach { print("$it ") }
