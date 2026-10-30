# 题目：3046. 分割数组（Split the Array）
# 核心思路：能分成两个等长且各自元素互不相同的数组，等价于任何数字的出现次数都不超过 2。
# 时间复杂度：O(n)，一次计数；空间复杂度：O(V)，哈希表保存不同数字的频次。
class Solution:  # LeetCode 约定的题解类
    def isPossibleToSplit(self, nums: List[int]) -> bool:  # nums：待分割的数组，返回能否分成两个等长且各自元素互不相同的数组
        return max(Counter(nums).values()) < 3  # 统计各数字频次；最大频次小于 3 说明每个值最多出现两次，可左右各放一个，因此一定能均分
