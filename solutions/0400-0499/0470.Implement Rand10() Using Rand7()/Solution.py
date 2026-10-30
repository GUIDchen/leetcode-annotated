# 题目：470. 用 Rand7() 实现 Rand10()（Implement Rand10() Using Rand7()）
# 思路：两次 rand7 组合出 1..49 的均匀随机数，拒绝 41..49 只保留 1..40，再取模映射到 1..10，40 是 10 的倍数故概率均等。
# 时间复杂度：期望 O(1)（每次接受概率 40/49）；空间复杂度：O(1)。
# The rand7() API is already defined for you.
# def rand7():
# @return a random integer in the range 1 to 7


class Solution:  # LeetCode 约定的题解类
    def rand10(self):  # 用 rand7 等概率生成 1..10
        """
        :rtype: int
        """
        while 1:  # 拒绝采样：落在拒绝区就重试
            i = rand7() - 1  # 取 0..6
            j = rand7()  # 取 1..7
            x = i * 7 + j  # 组合后等概率得到 1..49 中每个整数
            if x <= 40:  # 只保留 1..40，保证是 10 的倍数
                return x % 10 + 1  # 映射到 1..10，每个值恰好出现 4 次
