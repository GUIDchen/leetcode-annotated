# 题目：34. 在排序数组中查找元素的第一个和最后一个位置（Find First and Last Position of Element in Sorted Array）
# 思路：数组升序，用 bisect_left 分别求 target 与 target+1 的插入点 l、r，区间 [l, r-1] 即全部 target 的下标。
# 时间复杂度：O(log n)，两次二分；空间复杂度：O(1)，只用了常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def searchRange(self, nums: List[int], target: int) -> List[int]:  # nums 是升序数组，target 是目标值；返回 [起点, 终点]，找不到时返回 [-1, -1]
        l = bisect_left(nums, target)  # bisect_left 返回第一个 ≥ target 的位置，也就是第一个 target 的下标
        r = bisect_left(nums, target + 1)  # 同理求出第一个 ≥ target+1（即第一个 > target）的位置，它比最后一个 target 大 1
        return [-1, -1] if l == r else [l, r - 1]  # l == r 说明没有 target，返回 [-1, -1]；否则最后一个 target 的下标是 r-1
