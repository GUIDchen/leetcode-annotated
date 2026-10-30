# 题目：2789. 合并后数组中的最大元素（Largest Element in an Array after Merge Operations）
# 思路：从右往左原地合并，nums[i] <= nums[i + 1] 时把右侧已合并的段并到左侧，最后取数组最大值。
# 时间复杂度：O(n)，一次反向遍历加一次 max；空间复杂度：O(1)，只做原地修改。
class Solution:  # LeetCode 约定的题解类
    def maxArrayValue(self, nums: List[int]) -> int:  # nums：可以进行合并操作的数组
        for i in range(len(nums) - 2, -1, -1):  # 从倒数第二个位置向左逐位尝试合并
            if nums[i] <= nums[i + 1]:  # 左边不大于右边，说明可以把右边这一段整体并到左边
                nums[i] += nums[i + 1]  # 原位累加，nums[i] 变成合并后这一段的和
        return max(nums)  # 遍历完成后数组中的最大值就是答案
