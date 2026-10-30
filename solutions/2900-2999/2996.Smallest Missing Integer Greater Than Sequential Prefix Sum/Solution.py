# 题目：2996. 大于等于顺序前缀和的最小缺失整数（Smallest Missing Integer Greater Than Sequential Prefix Sum）
# 核心思路：先沿 nums 求出最长的「连续递增且步长为 1」前缀之和 s，再用集合从小到大跳过已经出现过的数，第一个缺口就是答案。
# 时间复杂度：O(n)，一次遍历加一次值域内跳跃；空间复杂度：O(n)，集合最多保存 n 个不同数值。
class Solution:  # LeetCode 约定的题解类
    def missingInteger(self, nums: List[int]) -> int:  # nums 是正整数列表，返回大于等于顺序前缀和的最小缺失整数
        s = nums[0]  # 顺序前缀和从第一个元素开始
        for x, y in pairwise(nums):  # pairwise 依次给出相邻对 (x, y)，只需判断两者是否连续
            if x + 1 != y:  # 相邻两数不连续，顺序前缀在此断开
                break  # 立即停止累加
            s += y  # 连续则把 y 并进前缀和
        st = set(nums)  # 用集合记录所有出现过的数值，查询为常数时间
        while s in st:  # 从 s 开始跳过已经出现过的数
            s += 1  # 该数存在，试下一个
        return s  # 找到最小缺失整数并返回
