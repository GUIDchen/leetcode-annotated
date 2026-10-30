# 题目：1753. 移除石子的最大得分（Maximum Score From Removing Stones）
# 思路：每轮从当前最多的两堆中各减一，循环到「第二多的那堆」为空为止，轮数就是最大得分。
# 时间复杂度：O(n)，n = a + b + c，每轮石子总数减少 2；空间复杂度：O(1)，只用一个长度为 3 的列表。
class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, a: int, b: int, c: int) -> int:  # a、b、c 为三堆石子的初始个数
        s = sorted([a, b, c])  # 升序排序，此时 s[1]、s[2] 就是当前最大的两堆
        ans = 0  # 累计得分，即成功操作的次数
        while s[1]:  # 第二多的堆非空，说明仍有两堆可以同时各取一颗
            ans += 1  # 本次操作得 1 分
            s[1] -= 1  # 从第二多的堆取走一颗石子
            s[2] -= 1  # 从最多的堆取走一颗石子（两堆必须不同）
            s.sort()  # 重新排序，让下一轮继续取到当前最大的两堆
        return ans  # 循环结束时得到的轮数就是最大得分
