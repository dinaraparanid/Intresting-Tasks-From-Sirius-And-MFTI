// Задача о рюкзаке с восстановлением ответа

fun calc(
    a: Int,
    w: Int,
    dp: Array<IntArray>,
    things: Array<Pair<Int, Int>>,
    ans: MutableList<Int> = mutableListOf()
): MutableList<Int> {
    if (dp[a][w] == 0)
        return ans
 
    when {
        dp[a - 1][w] == dp[a][w] -> ans.addAll(calc(a - 1, w, dp, things))
        else -> {
            ans.addAll(calc(a - 1, w - things[a - 1].first, dp, things))
            ans.add(a)
        }
    }
 
    return ans
}
 
fun main() {
    val (n, m) = readLine()!!.split(' ').map { it.toInt() }
    val things = readLine()!!
        .split(' ')
        .map { it.toInt() }
        .zip(readLine()!!.split(' ').map { it.toInt() })
        .toTypedArray()
 
    val dp = Array(n + 1) { IntArray(m + 1) { 0 } }
 
    for (a in 1..n) {
        for (w in 1..m) {
            dp[a][w] = when {
                w >= things[a - 1].first -> maxOf(
                    dp[a - 1][w],
                    dp[a - 1][w - things[a - 1].first] + things[a - 1].second
                )
                else -> dp[a - 1][w]
            }
        }
    }
 
    val ans = calc(n, m, dp, things)
    println(ans.size)
    ans.forEach { print("$it ") }
