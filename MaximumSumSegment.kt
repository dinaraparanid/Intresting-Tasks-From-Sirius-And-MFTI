// Найти подотрезок с максимальной суммой

fun main() {
    val reader = System.`in`.bufferedReader()
 
    var maxSum = (-2e9).toInt()
    var prtSum = 0
    var bestI = 0
    var bestQ = 0
    var minus = -1
 
    reader
        .readLines()
        .last()
        .trim()
        .split(' ')
        .map { it.toInt() }
        .toIntArray()
        .forEachIndexed { ind, x ->
            prtSum += x
 
            if (maxSum < prtSum) {
                bestI = minus + 1
                bestQ = ind
                maxSum = prtSum
            }
 
            if (prtSum < 0) {
                minus = ind
                prtSum = 0
            }
        }
 
    print("${bestI + 1} ${bestQ + 1} $maxSum")
