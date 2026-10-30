# 题目：442. 数组中重复的数据（Find All Duplicates in an Array）
# 思路：利用值域 1..n，原地把每个值 x 交换到下标 x-1 的位置；再扫一遍，位置上不是 i+1 的值就是重复出现的那个。
# 复杂度：时间复杂度 O(n)，每个元素最多被交换常数次；空间复杂度 O(1)，除返回值外只用原数组。
class Solution:  # 题解类：找出数组中所有出现两次的元素
    def findDuplicates(self, nums: List[int]) -> List[int]:  # nums 中每个元素出现一次或两次，返回所有出现两次的元素
        for i in range(len(nums)):  # 逐个位置处理，把下标 i 上的值送到它应该在的位置
            while nums[i] != nums[nums[i] - 1]:  # 值 x 应该在位置 x-1；只要还没归位就继续交换
                nums[nums[i] - 1], nums[i] = nums[i], nums[nums[i] - 1]  # 元组解包一次完成交换，把 nums[i] 送到目标位置
        return [v for i, v in enumerate(nums) if v != i + 1]  # 位置 i 上不是 i+1，说明该值出现了两次，用列表推导收集
