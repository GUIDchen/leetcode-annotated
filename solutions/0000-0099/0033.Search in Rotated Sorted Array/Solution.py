# 题目：33. 搜索旋转排序数组（Search in Rotated Sorted Array）
# 思路：改进的二分查找。每次看中点 mid 落在左半段还是右半段，再判断 target 是否落在该侧的有序区间内，从而决定收缩哪一侧边界；循环收敛到唯一候选后验证它是否等于 target。
# 时间复杂度：O(log n)，每次区间折半；空间复杂度：O(1)，只用常数个边界变量。
class Solution:  # LeetCode 约定的题解类
    def search(self, nums: List[int], target: int) -> int:  # nums：旋转后的升序数组；target：要找的值；返回下标或 -1
        n = len(nums)  # 数组长度，用于判断右半段的上界
        left, right = 0, n - 1  # 二分区间为闭区间 [left, right]
        while left < right:  # 区间长度大于 1 时继续二分；退出时 left == right 只剩唯一候选
            mid = (left + right) >> 1  # 取中点，右移一位等价于向下取整的除以 2
            if nums[0] <= nums[mid]:  # mid 落在左半段：nums[0..mid] 是单调递增的
                if nums[0] <= target <= nums[mid]:  # target 落在这一有序区间内部
                    right = mid  # 只需在左半边找，mid 仍可能是答案
                else:  # target 不在这个有序区间里
                    left = mid + 1  # 排除 mid 及其左侧，去右半边找
            else:  # mid 落在右半段：nums[mid..n-1] 是单调递增的
                if nums[mid] < target <= nums[n - 1]:  # target 落在右侧有序区间内部（不含 mid）
                    left = mid + 1  # 去右半边找
                else:  # 否则目标只可能在左半边
                    right = mid  # 收缩右边界，保留 mid 作为候选
        return left if nums[left] == target else -1  # 收敛后的唯一候选等于目标就返回下标，否则说明不存在
