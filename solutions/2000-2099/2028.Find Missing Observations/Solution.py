# 题目：2028. 找出缺失的观测数据（Find Missing Observations）
# 思路：缺失部分必须凑出的和 s = 总个数 × 平均值 - 已知观测值之和；先判断 s 是否落在 [n, 6n]，再把 s 平均分成 n 份，余数逐个补给前面若干份。
# 时间复杂度：O(m + n)，m 为已知观测值个数；空间复杂度：O(n)，用于存放答案。
class Solution:  # LeetCode 约定的题解类
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:  # rolls 是已知观测值，mean 是全体平均值，n 是缺失的观测次数
        m = len(rolls)  # 已知观测值的个数 m
        s = (n + m) * mean - sum(rolls)  # 缺失部分的总和 = 全体总和 - 已知部分之和
        if s > n * 6 or s < n:  # 骰子点数只能是 1~6，缺失和越界就说明无解
            return []  # 无解时返回空列表
        ans = [s // n] * n  # 先按向下取整的平均值分配 n 份
        for i in range(s % n):  # 余数共 s % n 个，逐个补给开头的若干位置
            ans[i] += 1  # 每个位置补 1，补完总和正好等于 s
        return ans  # 返回任意一组满足条件的缺失观测值
