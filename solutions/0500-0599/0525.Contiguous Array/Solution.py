# 题目：525. 连续数组（Contiguous Array）
# 思路：把 0 看成 -1，问题变成求和为 0 的最长子数组；前缀和相同即中间区间的 0 与 1 数量相等。
# 时间复杂度：O(n)，一次遍历并哈希表 O(1) 查询；空间复杂度：O(n)，最坏存 n 个不同前缀和。
class Solution:  # LeetCode 约定的题解类
    def findMaxLength(self, nums: List[int]) -> int:  # nums：只含 0/1 的数组；返回 0 与 1 数量相等的连续子数组最大长度
        d = {0: -1}  # 前缀和 → 最早下标；预置 0 对应 -1，让从头开始的区间也能被计算
        ans = s = 0  # ans 记录最大长度，s 记录当前前缀和，一起初始化
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            s += 1 if x else -1  # 1 记作 +1、0 记作 -1
            if s in d:  # 该前缀和以前出现过，可以构成合法区间
                ans = max(ans, i - d[s])  # 用「当前下标 - 最早下标」更新最大长度
            else:  # 该前缀和是第一次出现
                d[s] = i  # 记录最左下标，让后续区间尽量长
        return ans  # 返回最大长度，找不到时就是 0
