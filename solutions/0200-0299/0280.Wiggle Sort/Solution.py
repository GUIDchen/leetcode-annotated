# 题目：280. 摆动排序（Wiggle Sort）🔒
# 思路：按下标奇偶交替约束相邻元素大小关系，从左到右遇到不满足就交换当前与前一个元素，一遍扫描即可完成。
# 时间复杂度：O(n)，只扫描一次；空间复杂度：O(1)，原地交换。
class Solution:  # LeetCode 约定的题解类
    def wiggleSort(self, nums: List[int]) -> None:  # nums 是待原地调整的数组，返回 None
        """
        Do not return anything, modify nums in-place instead.
        """
        for i in range(1, len(nums)):  # 从第二个元素开始逐个修复相邻的大小关系
            if (i % 2 == 1 and nums[i] < nums[i - 1]) or (  # 奇数下标本应更大，若反而更小就说明这里需要交换
                i % 2 == 0 and nums[i] > nums[i - 1]  # 偶数下标本应更小，若反而更大同样需要交换
            ):  # 两个条件任一成立，当前元素就违反了摆动关系
                nums[i], nums[i - 1] = nums[i - 1], nums[i]  # 交换后局部恢复摆动，且不会破坏左侧已修好的部分
