# 题目：908. 最小差值 I（Smallest Range I）
# 核心思路：只有最大值和最小值决定差值，两者各自最多向中间调整 k，所以答案是 max(0, max - min - 2k)。
# 时间复杂度：O(n)，一次遍历求最值；空间复杂度：O(1)，只存两个极值。
class Solution:  # LeetCode 约定的题解类
    def smallestRangeI(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：每个元素最多可加减的幅度；返回最小的最大差值
        mx, mi = max(nums), min(nums)  # 先求出数组的最大值与最小值
        return max(0, mx - mi - k * 2)  # 最大值减 k、最小值加 k 使差值缩小 2k，结果不能为负
