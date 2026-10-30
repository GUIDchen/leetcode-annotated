# 题目：2206. 将数组划分成相等数对（Divide Array Into Equal Pairs）
# 核心思路：能两两配对等价于每个数值出现的次数都是偶数，用 Counter 统计频次后一次性判断全部频次。
# 时间复杂度：O(n)，一次计数加一次遍历；空间复杂度：O(U)，U 是不同数值的个数。
class Solution:  # LeetCode 约定的题解类
    def divideArray(self, nums: List[int]) -> bool:  # nums 是待划分的数组
        cnt = Counter(nums)  # 统计每个数值出现的次数：键是数值、值是频次
        return all(v % 2 == 0 for v in cnt.values())  # 只有全部频次都是偶数才能两两配对
