# 题目：1064. 不动点（Fixed Point）
# 思路：数组严格递增，故 arr[i] - i 单调不减，可二分出第一个 arr[i] >= i 的位置再校验它是否等于 i。
# 时间复杂度：O(log n)，一次二分；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def fixedPoint(self, arr: List[int]) -> int:  # arr：严格递增的非负整数数组；返回最小的满足 arr[i] == i 的下标，不存在则返回 -1
        left, right = 0, len(arr) - 1  # 二分区间 [left, right]，若不动点存在必定落在该区间内
        while left < right:  # 区间还没收缩到单点就继续二分
            mid = (left + right) >> 1  # 取中点（右移一位等价于整除 2）
            if arr[mid] >= mid:  # 中点值不小于下标，说明不动点可能在 mid 或更左侧
                right = mid  # 保留 mid 作为新的右边界
            else:  # 否则 arr[mid] < mid，mid 及其左侧都不可能是答案
                left = mid + 1  # 左边界右移到 mid + 1
        return left if arr[left] == left else -1  # 校验收敛到的下标是否真的满足 arr[i] == i，不满足说明没有不动点
