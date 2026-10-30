# 题目：724. 寻找数组的中心下标（Find Pivot Index）
# 思路：把总和当作初始「右侧和」，从左往右遍历时每步先扣掉当前元素，此时 left/right 恰为左右两侧和，相等即为答案。
# 时间复杂度：O(n)，一次求和加一次遍历；空间复杂度：O(1)，只用两个累加变量。
class Solution:  # LeetCode 约定的题解类
    def pivotIndex(self, nums: List[int]) -> int:  # nums：输入数组
        left, right = 0, sum(nums)  # left 为左侧和，right 初始为整个数组的和
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            right -= x  # 先扣除当前元素，使 right 变成 i 右侧（不含 i）的和
            if left == right:  # 左右两侧和相等，i 就是中心下标
                return i  # 题目要求最左边那个，找到即可返回
            left += x  # 把当前元素累加进左侧和，继续向右
        return -1  # 遍历完仍不存在中心下标
