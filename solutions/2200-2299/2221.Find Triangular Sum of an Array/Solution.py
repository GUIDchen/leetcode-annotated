# 题目：2221. 数组的三角和（Find Triangular Sum of an Array）
# 思路：原地模拟每一层的相邻求和取模，每轮有效长度减一，最后剩下的 nums[0] 就是三角和。
# 时间复杂度：O(n²)，共做 n-1 轮、每轮长度递减；空间复杂度：O(1)，只借用输入数组原地更新。
class Solution:  # LeetCode 约定的题解类
    def triangularSum(self, nums: List[int]) -> int:  # nums：输入数组，返回逐层「相邻求和取个位」后的最终值
        for k in range(len(nums) - 1, 0, -1):  # k 是当前层的长度，从 n-1 递减到 1
            for i in range(k):  # 在本层内从左到右处理每一对相邻元素
                nums[i] = (nums[i] + nums[i + 1]) % 10  # 相邻两数相加后只保留个位，写回前一个位置
        return nums[0]  # 所有层合并完毕，首元素就是数组的三角和
