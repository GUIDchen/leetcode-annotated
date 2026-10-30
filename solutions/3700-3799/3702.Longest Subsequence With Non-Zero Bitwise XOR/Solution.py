# 题目：3702. 按位异或非零的最长子序列（Longest Subsequence With Non-Zero Bitwise XOR）
# 核心思路：先求全数组异或和：若不为 0，整个数组就是答案；若为 0 且存在非零元素，去掉任意一个非零元素即可让异或非零，答案为 n-1；若全是 0，则任何子序列异或都为 0，答案为 0。
# 复杂度：时间 O(n)，只扫一遍数组；空间 O(1)，只有几个计数器。
class Solution:  # LeetCode 约定的题解类
    def longestSubsequence(self, nums: List[int]) -> int:  # 返回异或和非零的最长子序列长度
        n = len(nums)  # 数组长度
        xor = cnt0 = 0  # xor 累计全体异或和，cnt0 统计 0 的个数
        for x in nums:  # 遍历数组的每个元素
            xor ^= x  # 把当前元素异或进全体异或和
            cnt0 += int(x == 0)  # 当前元素为 0 时让计数器加一
        if xor:  # 全体异或和已经非零，可以直接全选
            return n  # 整段数组就是最长子序列
        if cnt0 == n:  # 数组元素全为 0，任何子序列异或都为 0
            return 0  # 不存在满足条件的子序列
        return n - 1  # 否则去掉任意一个非零元素即可让异或非零
