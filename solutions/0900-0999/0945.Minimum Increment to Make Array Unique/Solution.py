# 题目：945. 使数组唯一的最小增量（Minimum Increment to Make Array Unique）
# 思路：排序后贪心，用 y 记录上一个数最终被抬到的值，当前数至少抬到 y+1，累加抬升量。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minIncrementForUnique(self, nums: List[int]) -> int:  # nums 是整数列表，返回使元素互不相同的最小增量次数
        nums.sort()  # 原地升序排序，便于从左到右贪心
        ans, y = 0, -1  # ans 累计增量；y 是上一个数最终被抬到的值
        for x in nums:  # 按升序依次处理每个数
            y = max(y + 1, x)  # 当前数至少要等于 y+1，本身更大则保持不变
            ans += y - x  # 累加把 x 抬到 y 的增量代价
        return ans  # 返回最小总增量
