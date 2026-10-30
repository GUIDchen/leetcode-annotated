# 题目：747. 至少是其他数字两倍的最大数（Largest Number At Least Twice of Others）
# 核心思路：取出最大的两个数 x、y，只要 x >= 2y 就说明最大数满足「至少是其他数字两倍」，返回它的下标，否则返回 -1。
# 时间复杂度：O(n)，nlargest(2) 只需一趟扫描；空间复杂度：O(1)，只存两个数。
class Solution:  # LeetCode 约定的题解类
    def dominantIndex(self, nums: List[int]) -> int:  # nums 是待检查的数组，题目保证 n >= 2
        x, y = nlargest(2, nums)  # x 是最大值，y 是次大值；题目保证至少两个元素，所以可以解包
        return nums.index(x) if x >= 2 * y else -1  # 最大值达到次大值的两倍就返回其下标，否则返回 -1
