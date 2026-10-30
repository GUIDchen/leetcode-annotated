# 题目：1673. 找出最具竞争力的子序列（Find the Most Competitive Subsequence）
# 思路：维护单调递增栈。当前元素更小且删掉栈顶后仍能凑够 k 个时弹栈，最终栈内即为字典序最小的长度 k 子序列。
# 时间复杂度：O(n)，每个元素最多入栈出栈各一次；空间复杂度：O(k)，栈最多保存 k 个元素。
class Solution:  # LeetCode 约定的题解类
    def mostCompetitive(self, nums: List[int], k: int) -> List[int]:  # nums：原数组；k：需要保留的子序列长度
        stk = []  # 用列表模拟单调栈，栈内元素保持递增
        n = len(nums)  # 记录数组长度，判断是否还能继续删除
        for i, v in enumerate(nums):  # 同时取得下标 i 与元素值 v
            while stk and stk[-1] > v and len(stk) + n - i > k:  # 栈顶更大就弹掉；len(stk) + n - i > k 保证剩余元素仍够凑满 k 个
                stk.pop()  # 弹出较大栈顶，让更小的当前元素上位，字典序更小
            if len(stk) < k:  # 栈未满 k 个才放入当前元素
                stk.append(v)  # 当前元素入栈
        return stk  # 返回长度为 k 的最小字典序子序列
