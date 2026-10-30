# 题目：852. 山脉数组的峰顶索引（Peak Index in a Mountain Array）
# 思路：在 [1, n-2] 上二分：若 arr[mid] > arr[mid+1] 说明峰顶在 mid 或其左侧，否则在 mid 右侧。
# 时间复杂度：O(log n)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # 题解类
    def peakIndexInMountainArray(self, arr: List[int]) -> int:  # arr 是山脉数组：先严格递增再严格递减
        left, right = 1, len(arr) - 2  # 峰顶不可能在两端，只在 [1, n-2] 中二分
        while left < right:  # 二分到区间只剩一个位置
            mid = (left + right) >> 1  # 取中点
            if arr[mid] > arr[mid + 1]:  # 处于下降段，峰顶在 mid 或其左侧
                right = mid  # 保留 mid，右边界左移
            else:  # 处于上升段，峰顶在 mid 右侧
                left = mid + 1  # 左边界右移到 mid+1
        return left  # 收敛位置即峰顶下标
