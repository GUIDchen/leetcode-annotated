# 题目：594. 最长和谐子序列（Longest Harmonious Subsequence）
# 思路：用 Counter 统计每个值出现的次数，只考察 x 与 x+1 同时存在的取值组合，把两者次数相加取最大值。
# 时间复杂度：O(n)，一次计数加一次遍历；空间复杂度：O(n)，计数器最多存 n 个不同的值。
class Solution:  # LeetCode 约定的题解类
    def findLHS(self, nums: List[int]) -> int:  # nums 是输入数组，返回最长和谐子序列的长度
        cnt = Counter(nums)  # 统计每个值出现的次数：键是元素值，值是出现次数
        return max((c + cnt[x + 1] for x, c in cnt.items() if cnt[x + 1]), default=0)  # 生成器里只保留 x+1 也出现的组合，default=0 处理没有任何组合的情况
