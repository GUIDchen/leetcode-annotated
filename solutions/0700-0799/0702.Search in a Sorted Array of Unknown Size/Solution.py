# 题目：702. 搜索长度未知的有序数组（Search in a Sorted Array of Unknown Size 🔒）
# 思路：先用倍增法把右端点扩大到取值 >= target 的位置，确定答案落在 [r/2, r] 内，再在该区间做标准二分查找。
# 时间复杂度：O(log n)，倍增与二分都是对数级；空间复杂度：O(1)，只用了常数个变量。
# """
# This is ArrayReader's API interface.
# You should not implement it, or speculate about its implementation
# """
# class ArrayReader:
#    def get(self, index: int) -> int:


class Solution:  # LeetCode 约定的题解类
    def search(self, reader: "ArrayReader", target: int) -> int:  # reader 提供按下标取值（越界返回 2^31-1），返回 target 的下标或 -1
        r = 1  # 右端点从 1 开始，用倍增的方式向外扩展
        while reader.get(r) < target:  # 右端点的值还小于目标，说明答案在更右边
            r <<= 1  # 左移一位等价于乘 2，把搜索区间右边界翻倍
        l = r >> 1  # 上一次的右端点（除以 2）必然是第一个可能的下界
        while l < r:  # 在 [l, r] 上做二分查找，区间收敛到单点
            mid = (l + r) >> 1  # 取中点，右移一位即向下取整的折半
            if reader.get(mid) >= target:  # 中点的值不小于目标，答案在左半边（含 mid）
                r = mid  # 收缩右边界到 mid
            else:  # 中点的值小于目标，答案在右半边
                l = mid + 1  # 收缩左边界到 mid + 1
        return l if reader.get(l) == target else -1  # 最终位置的取值等于目标则返回下标，否则说明不存在
