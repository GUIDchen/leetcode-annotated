# 题目：162. 寻找峰值（Find Peak Element）
# 核心思路：比较 nums[mid] 与 nums[mid+1] 判断上坡还是下坡，用二分不断收缩到必然包含峰值的半边，最后剩下的位置就是峰值。
# 时间复杂度：O(log n)，每轮区间减半；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findPeakElement(self, nums: List[int]) -> int:  # nums：相邻元素互不相同的数组，两端视为 -∞，因此一定存在峰值
        left, right = 0, len(nums) - 1  # 二分区间 [left, right]，初始覆盖整个数组
        while left < right:  # 区间只剩一个下标时它就是峰值，退出循环
            mid = (left + right) >> 1  # 位运算取中点，等价于 (left + right) // 2
            if nums[mid] > nums[mid + 1]:  # 处于下坡：峰值在 mid 及其左侧
                right = mid  # 保留 mid，因为它自身可能就是峰值
            else:  # 否则处于上坡：峰值必在 mid 右侧
                left = mid + 1  # 丢弃 mid，它比右邻居小，不可能是峰值
        return left  # 返回唯一剩下的峰值下标
