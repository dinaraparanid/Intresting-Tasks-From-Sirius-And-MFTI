// Наибольшая общая подпоследовательность с восстановлением ответа

fun main() {
    val read = {
        readLine()!!.toInt() to readLine()!!.split(' ').map { it.toInt() }.toIntArray()
    }

    val (n, fst) = read()
    val (m, sec) = read()

    MutableList(n + 1) { MutableList(m + 1) { 0 } }
        .also {
            (1..n).forEach { i ->
                (1..m).forEach { q ->
                    when {
                        fst[i - 1] == sec[q - 1] -> it[i][q] = it[i - 1][q - 1] + 1
                        else -> it[i][q] = maxOf(it[i - 1][q], it[i][q - 1])
                    }
                }
            }
        }
        .also { println(it[n][m]) }
        .let {
            mutableListOf<Int>()
                .also { ans ->
                    var i = n
                    var q = m

                    while (i > 0 && q > 0) {
                        when {
                            fst[i - 1] == sec[q - 1] -> {
                                ans.add(fst[i - 1])
                                i--; q--
                            }
                            it[i - 1][q] == it[i][q] -> i--
                            else -> q--
                        }
                    }
                }
                .let { ans -> ans.asReversed().forEach { print("$it ") } }
        }
}
