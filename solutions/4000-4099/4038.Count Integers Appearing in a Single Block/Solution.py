# 题目：4038. 计算单个区间中出现的整数数量 / Count Integers Appearing in a Single Block
# 核心思路：只在每个连续块的首个位置计数，得到每个值落在多少个块中，最后统计块数为 1 的值的个数
# 复杂度：时间复杂度 O(n + V)，空间复杂度 O(V)（V 为数值范围）
class Solution:  # 定义 LeetCode 题解类
    def countSpecialIntegers(self, nums: List[int]) -> int:  # 统计只在单个连续块中出现过的整数个数
        cnt = Counter(x for i, x in enumerate(nums) if i == 0 or x != nums[i - 1])  # 只把每个连续块的首个元素计入，cnt[x] 即 x 出现在几个块中
        return sum(v == 1 for v in cnt.values())  # 块个数恰好为 1 的值的个数就是答案
