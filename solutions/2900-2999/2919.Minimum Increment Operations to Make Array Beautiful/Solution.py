# 题目：2919. 使数组变美的最小增量运算数（Minimum Increment Operations to Make Array Beautiful）
# 思路：动态规划，f/g/h 表示最近被抬高的元素是 i-2 / i-1 / i 时的最小代价，新状态 = 三者最小值 + 把当前元素抬到 k 的代价。
# 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用了三个滚动变量。
class Solution:  # LeetCode 约定的题解类
    def minIncrementOperations(self, nums: List[int], k: int) -> int:  # nums：目标数组；k：任意连续三个元素之和至少为 k
        f = g = h = 0  # 滚动 DP：最近被抬高的元素是 i-2 / i-1 / i 时的最小代价，初始都为 0
        for x in nums:  # 从左到右处理每个元素
            f, g, h = g, h, min(f, g, h) + max(k - x, 0)  # 同时右移状态，并让当前元素达标：前态取最小再加抬升代价
        return min(f, g, h)  # 三种结尾都合法，取最小值
