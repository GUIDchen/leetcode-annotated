# 题目：2965. 找出缺失和重复的数字（Find Missing and Repeated Values）
# 思路：用计数数组统计 1..n*n 每个数字出现的次数，次数为 2 的是重复的数，次数为 0 的是缺失的数。
# 时间复杂度：O(n^2)，遍历矩阵与计数数组各一遍；空间复杂度：O(n^2)，计数数组长度为 n*n+1。
class Solution:  # LeetCode 约定的题解类
    def findMissingAndRepeatedValues(self, grid: List[List[int]]) -> List[int]:  # grid 是 n×n 的矩阵，返回 [重复的数, 缺失的数]
        n = len(grid)  # n 是矩阵边长，数字范围是 1..n*n
        cnt = [0] * (n * n + 1)  # 计数数组，cnt[v] 表示数字 v 出现的次数
        for row in grid:  # 按行遍历矩阵
            for v in row:  # 遍历这一行的每个数字
                cnt[v] += 1  # 该数字出现次数加一
        ans = [0] * 2  # 答案数组：下标 0 放重复的数，下标 1 放缺失的数
        for i in range(1, n * n + 1):  # 遍历 1..n*n 的全部数字
            if cnt[i] == 2:  # 出现两次的就是重复的数
                ans[0] = i  # 记录重复的数
            if cnt[i] == 0:  # 一次都没出现的就是缺失的数
                ans[1] = i  # 记录缺失的数
        return ans  # 返回两个答案
