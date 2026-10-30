# 题目：719. 找出第 K 小的数对距离（Find K-th Smallest Pair Distance）
# 思路：先排序，把「第 k 小的距离」转化为对距离二分：count(dist) 统计距离不超过 dist 的数对个数，它是单调不减的。
# 时间复杂度：O(n log n + n log W)，W 为最大差值；空间复杂度：O(1)（不计排序开销）。
class Solution:  # LeetCode 约定的题解类
    def smallestDistancePair(self, nums: List[int], k: int) -> int:  # nums：非负数组；k：第 k 小（1-based）
        def count(dist):  # 内部函数：统计距离不超过 dist 的数对个数
            cnt = 0  # 计数器
            for i, b in enumerate(nums):  # i 是右端点下标，b 是右端点的值
                a = b - dist  # 左端点至少要达到的值，才能让距离不超过 dist
                j = bisect_left(nums, a, 0, i)  # 在已排序的 [0, i) 区间内二分第一个 >= a 的位置，保证左端点在 i 之前
                cnt += i - j  # [j, i-1] 共 i - j 个左端点满足条件
            return cnt  # 返回满足条件的数对总数

        nums.sort()  # 先排序（闭包里的 count 使用的就是排序后的 nums）
        return bisect_left(range(nums[-1] - nums[0]), k, key=count)  # 在 range 上按 key 二分，找第一个 count(dist) >= k 的距离；若都不满足则返回右端点即最大距离
