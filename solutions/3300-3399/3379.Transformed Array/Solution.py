# 题目：3379. 转换数组（Transformed Array）
# 思路：把 nums[i] 看作环形偏移量。先对 n 取模得到相对位移，再补 n 抵消负数，最后整体 % n 得到合法下标。
# 时间复杂度：O(n)；空间复杂度：O(n)，用于存放返回数组。
class Solution:  # LeetCode 约定的题解类
    def constructTransformedArray(self, nums: List[int]) -> List[int]:  # nums：输入数组；返回等长的转换后数组
        n = len(nums)  # 数组长度，用于环形取模
        return [nums[(i + x % n + n) % n] for i, x in enumerate(nums)]  # 列表推导：x % n 取相对位移，+n 处理负偏移，再 %n 映射回合法下标
