# 题目：2294. 划分数组使最大差为 K（Partition Array Such That Maximum Difference Is K）
# 思路：升序排序后贪心切分，当前元素与当前组最小值之差超过 k 就另起一组，这样组数最少。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序所需的辅助空间。
class Solution:  # LeetCode 约定的题解类
    def partitionArray(self, nums: List[int], k: int) -> int:  # nums：待划分的数组；k：每组内最大值与最小值之差的上限
        nums.sort()  # 升序排序：最优划分中同一组的元素在排序后必然连续，便于贪心切分
        ans, a = 1, nums[0]  # ans 记录组数（至少 1 组）；a 记录当前组的最小值
        for b in nums:  # 从左到右依次考虑每个元素
            if b - a > k:  # 与当前组最小值之差超过 k，说明必须另起一组
                a = b  # b 成为新一组的最小值
                ans += 1  # 组数加一
        return ans  # 返回最少分组数
