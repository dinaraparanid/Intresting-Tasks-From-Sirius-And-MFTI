// Дейкстра на Котлине

import java.util.*

const val INF = 2e9.toInt()

internal object Cmp : Comparator<Pair<Int, Int>> {
    override fun compare(s1: Pair<Int, Int>, s2: Pair<Int, Int>): Int {
        if (s1.first != s2.first)
            return s1.first.compareTo(s2.first)
        return s1.second.compareTo(s2.second)
    }
}

fun main() {
    val n = (readLine() ?: return).toInt()
    val price = (readLine() ?: return).split(" ").map { x -> x.toInt() }
    val m = (readLine() ?: return).toInt()
    val gr = MutableList(n) { MutableList(0) { 0 to 0 } } // v / wt

    for (i in 0 until m) {
        val inp = (readLine() ?: return).split(' ').map { x -> x.toInt() }
        val v = inp.first() - 1
        val u = inp.last() - 1

        gr[v].add(u to price[v])
        gr[u].add(v to price[u])
    }

    val prev = MutableList(n) { -1 }
    val dist = MutableList(n) { INF }
    val se = TreeSet(Cmp)

    se.add(0 to 0)
    dist[0] = 0

    while (!se.isEmpty()) {
        val v = se.first().second
        se.remove(se.first())

        for ((u, wt) in gr[v]) {
            if (dist[v] + wt < dist[u]) {
                se.remove(dist[u] to u)
                dist[u] = dist[v] + wt
                se.add(dist[u] to u)
                prev[u] = v
            }
        }
    }

    println({ if (dist.last() == INF) -1 else dist.last() }())
}
