# 题目：2550. 猴子碰撞的方法数（Count Collisions of Monkeys on a Polygon）
# 思路：容斥。每只猴子 2 种走法共 2^n 种，其中只有全部顺时针、全部逆时针这 2 种不碰撞，答案为 2^n - 2。
# 时间复杂度：O(log n)，由内置 pow 的快速幂实现决定；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def monkeyMove(self, n: int) -> int:  # n 是猴子个数，也就是多边形的顶点数
        mod = 10**9 + 7  # 按题目要求对 1e9+7 取模
        return (pow(2, n, mod) - 2) % mod  # pow(2, n, mod) 是内置快速幂；减去 2 种全同向方案，% 保证结果非负
