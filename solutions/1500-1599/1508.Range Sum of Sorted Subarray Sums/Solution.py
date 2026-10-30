# 题目：1508. 子数组和排序后的区间和（Range Sum of Sorted Subarray Sums）
# 思路：枚举左右端点求出全部 n(n+1)/2 个子数组的和，排序后对第 left..right 项求和取模。
# 时间复杂度：O(n^2 log n)，生成 n^2 个和再排序；空间复杂度：O(n^2)，存放全部子数组和。
class Solution:  # LeetCode 约定的题解类
    def rangeSum(self, nums: List[int], n: int, left: int, right: int) -> int:  # nums：原数组；n：数组长度；left/right：区间端点（1-based）
        arr = []  # 保存所有子数组的和
        for i in range(n):  # i 为子数组左端点
            s = 0  # 以 i 开头的子数组的累加和
            for j in range(i, n):  # j 为右端点，逐步向右扩展
                s += nums[j]  # 累加得到 nums[i..j] 的和
                arr.append(s)  # 记录该子数组的和
        arr.sort()  # 升序排序，题目要求的是排序后的序列
        mod = 10**9 + 7  # 取模常量 10^9+7
        return sum(arr[left - 1 : right]) % mod  # 切片取出 1-based 区间 [left, right] 的和，再取模
