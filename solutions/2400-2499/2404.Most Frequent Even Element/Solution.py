# 题目：2404. 出现最频繁的偶数元素（Most Frequent Even Element）
# 思路：用 Counter 统计每个偶数的出现频次，再按「次数最多、数值最小」的规则选出答案。
# 时间复杂度：O(n)，统计与遍历各一遍；空间复杂度：O(n)，计数器最多保存 n 个不同的偶数。
class Solution:  # LeetCode 约定的题解类
    def mostFrequentEven(self, nums: List[int]) -> int:  # nums：输入整数列表，返回出现次数最多且数值最小的偶数
        cnt = Counter(x for x in nums if x % 2 == 0)  # 只统计偶数：Counter 累加每个偶数的出现次数
        ans, mx = -1, 0  # ans 记录答案（-1 表示还没有遇到偶数），mx 记录当前最大出现次数
        for x, v in cnt.items():  # 遍历计数器里的「偶数 → 次数」键值对
            if v > mx or (v == mx and ans > x):  # 次数更大，或次数相同但数值更小，都要更新答案
                ans, mx = x, v  # 同时更新答案偶数和当前最大次数
        return ans  # 没有偶数时 ans 仍是 -1，正好符合题目要求
