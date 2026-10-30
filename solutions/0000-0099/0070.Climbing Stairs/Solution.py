# 题目：70. 爬楼梯（Climbing Stairs）
# 思路：f(i) = f(i-1) + f(i-2)（最后一步走 1 阶或 2 阶），用两个滚动变量做线性递推。
# 时间复杂度：O(n)，递推 n 次；空间复杂度：O(1)，只保存相邻两项。
class Solution:  # LeetCode 约定的题解类
    def climbStairs(self, n: int) -> int:  # n：楼梯总阶数
        a, b = 0, 1  # a 对应 f(i-2)、b 对应 f(i-1)，初值为 f(0)=0、f(1)=1
        for _ in range(n):  # 递推 n 次，把 f(1) 推到 f(n)
            a, b = b, a + b  # 元组同时赋值：新的 a 变成旧的 b（f(i-1)），新的 b 变成 f(i-2)+f(i-1)
        return b  # 循环结束时 b 即 f(n)，也就是爬 n 阶的方法总数
