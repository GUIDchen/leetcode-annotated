# 3634. 使数组平衡的最少移除数目 / Minimum Removals to Balance Array
# 核心思路：排序后枚举区间左端点，用二分找到满足 max ≤ min×k 的最长区间，答案即 n 减去最长区间长度
# 时间复杂度 O(n log n)，空间复杂度 O(1)
#
class Solution:  # 题目要求实现的类
    def minRemoval(self, nums: List[int], k: int) -> int:  # 返回使数组平衡所需的最少移除元素个数
        nums.sort()  # 先排序，之后才能用二分和区间技巧
        cnt = 0  # cnt 记录最多可以同时保留的元素个数
        for i, x in enumerate(nums):  # 同时枚举区间左端点下标与取值
            j = bisect_right(nums, k * x)  # 二分找第一个大于 k*x 的位置，即可保留区间的右边界
            cnt = max(cnt, j - i)  # 更新最多可保留的元素个数
        return len(nums) - cnt  # 总长度减去可保留数目，就是最少移除数目
