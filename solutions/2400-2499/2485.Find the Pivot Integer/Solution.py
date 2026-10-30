# 题目：2485. 找出中枢整数（Find the Pivot Integer）
# 思路：从小到大枚举 x，用等差数列求和公式比较 1..x 与 x..n 的和是否相等，第一个相等的就是答案。
# 时间复杂度：O(n)，只枚举 n 个候选；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def pivotInteger(self, n: int) -> int:  # n：上界；返回满足 1+...+x == x+...+n 的 x，不存在则返回 -1
        for x in range(1, n + 1):  # 从小到大枚举候选中枢 x
            if (1 + x) * x == (x + n) * (n - x + 1):  # 两边都乘 2 后比较：(1+x)*x 是 1..x 的和的两倍，(x+n)*(n-x+1) 是 x..n 的和的两倍
                return x  # 第一个满足条件的 x 就是最小解，直接返回
        return -1  # 都没有命中，按题意返回 -1
