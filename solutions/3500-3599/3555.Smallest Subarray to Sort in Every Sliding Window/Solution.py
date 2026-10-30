# 题目：3555. 排序每个滑动窗口中最小的子数组（Smallest Subarray to Sort in Every Sliding Window）
# 思路：对每个长度为 k 的窗口，用一次循环同时从左、从右向中间扫描：左起扫描记录最右的“比前面最大值小”的位置（右端点 r），右起扫描记录最左的“比后面最小值大”的位置（左端点 l），区间 [l, r] 就是需要排序的最短子数组；若整段有序则答案为 0。
# 时间复杂度：O(n·k)，每个窗口线性扫描一次；空间复杂度：O(n-k+1)，用于存放每个窗口的答案。
class Solution:  # LeetCode 约定的题解类
    def minSubarraySort(self, nums: List[int], k: int) -> List[int]:  # nums：给定数组；k：窗口长度；返回每个窗口的最短排序子数组长度
        def f(i: int, j: int) -> int:  # f：求闭区间 [i, j] 内需要排序的最短子数组长度
            mi, mx = inf, -inf  # mi、mx：右起/左起扫描时分别见过的最小值、最大值
            l = r = -1  # l、r：需要排序区间的左、右端点，先置为 -1 表示尚未出现乱序
            for k in range(i, j + 1):  # 一次循环同时从左、从右向中间扫描
                if mx > nums[k]:  # 左起扫描：当前值比历史最大值小，说明它必须参与排序
                    r = k  # 记录最靠右的乱序位置
                else:  # 当前值不小于历史最大值，说明它已处在正确位置
                    mx = nums[k]  # 更新历史最大值
                p = j - k + i  # p：与 k 关于区间中点对称的、从右往左的下标
                if mi < nums[p]:  # 右起扫描：当前值比历史最小值大，说明它必须参与排序
                    l = p  # 记录最靠左的乱序位置
                else:  # 当前值不大于历史最小值，说明它已处在正确位置
                    mi = nums[p]  # 更新历史最小值
            return 0 if r == -1 else r - l + 1  # 没有乱序则整段已有序返回 0，否则区间长度 r-l+1 即答案

        n = len(nums)  # n：数组长度
        return [f(i, i + k - 1) for i in range(n - k + 1)]  # 枚举所有长度 k 的窗口并收集各自的答案
