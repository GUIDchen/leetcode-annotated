# 题目：3069. 将元素分配到两个数组中 I（Distribute Elements Into Two Arrays I）
# 核心思路：按题意模拟——两个数组分别以 nums[0]、nums[1] 起步，之后每个元素放到「末尾元素更大」的那个数组的末尾，最后把两数组拼接。
# 时间复杂度：O(n)，每个元素只比较与追加一次；空间复杂度：O(n)，两个数组共保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def resultArray(self, nums: List[int]) -> List[int]:  # nums：输入数组（长度至少为 2）；返回拼接后的结果数组
        arr1 = [nums[0]]  # arr1 以第一个元素作为初始唯一元素
        arr2 = [nums[1]]  # arr2 以第二个元素作为初始唯一元素
        for x in nums[2:]:  # 切片取出从下标 2 开始的剩余元素，逐个分配
            if arr1[-1] > arr2[-1]:  # 比较两个数组的末尾元素（-1 即最后一个），谁更大就放进谁
                arr1.append(x)  # arr1 末尾更大（或相等时也归 arr1），追加到 arr1
            else:  # else：arr2 末尾严格更大
                arr2.append(x)  # 追加到 arr2 末尾
        return arr1 + arr2  # 两个列表顺序拼接：arr1 在前、arr2 在后
