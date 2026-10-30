# 题目：509. 斐波那契数（Fibonacci Number）
# 思路：滚动变量迭代，a 保持 F(k)、b 保持 F(k+1)，每次用元组赋值同时更新，循环 n 次后 a 就是 F(n)。
# 时间复杂度：O(n)；空间复杂度：O(1)，只用两个变量。
class Solution:  # LeetCode 约定的题解类
    def fib(self, n: int) -> int:  # n：要求第 n 个斐波那契数
        a, b = 0, 1  # a 是 F(0)，b 是 F(1)
        for _ in range(n):  # 迭代 n 次，每次把 (a, b) 往后推一项
            a, b = b, a + b  # 同时更新：a 变成旧 b，b 变成两项之和
        return a  # 返回 F(n)
