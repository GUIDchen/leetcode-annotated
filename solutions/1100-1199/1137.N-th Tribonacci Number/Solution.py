# 题目：1137. 第 N 个泰波那契数（N-th Tribonacci Number）
# 思路：三项滚动的迭代：a、b、c 保存最近三项，每轮用元组交换整体前移。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def tribonacci(self, n: int) -> int:  # 求第 n 个泰波那契数，T(0)=0、T(1)=1、T(2)=1，之后每项是前三项之和
        a, b, c = 0, 1, 1  # 三个变量滚动保存最近三项
        for _ in range(n):  # 迭代 n 次，每轮把窗口往前推一项
            a, b, c = b, c, a + b + c  # 元组同时赋值：右边先用旧值 a+b+c 算好新项，再整体覆盖，无需临时变量
        return a  # 循环 n 次后 a 就是 T(n)
