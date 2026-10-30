# 题目：1838. 最高频元素的频数（Frequency of the Most Frequent Element）
# 思路：排序后用 accumulate 求前缀和，再二分答案 m，用相邻 m 个元素全提升到最大值所需代价判断 m 是否可行。
# 时间复杂度：O(n log n)，排序加二分；空间复杂度：O(n)，前缀和列表。
class Solution:  # LeetCode 约定的题解类
    def maxFrequency(self, nums: List[int], k: int) -> int:  # nums 是可自增的数组，k 是可用增量总和，返回最高频元素能达到的最大频数
        def check(m: int) -> bool:  # 内层判定函数，n 与 s 在定义之后才赋值，但调用时已经存在（闭包延迟绑定）
            for i in range(m, n + 1):  # 枚举窗口右端点 i，窗口是 nums[i-m .. i-1]
                if nums[i - 1] * m - (s[i] - s[i - m]) <= k:  # 全提升到最大值 nums[i-1] 的代价 = 最大值乘 m 减窗口和
                    return True  # 存在可行窗口，频数 m 可以达到
            return False  # 没有可行窗口，频数 m 达不到

        n = len(nums)  # 数组长度
        nums.sort()  # 先排序：最终被提升成同一个值的那批元素必然连续
        s = list(accumulate(nums, initial=0))  # 前缀和，长度 n+1，initial=0 让 s[0] 为 0
        l, r = 1, n  # 答案二分区间：频数最小为 1，最大为 n
        while l < r:  # 二分查找最大的可行 m
            mid = (l + r + 1) >> 1  # 向上取整的中点，配合 l = mid 才不会死循环
            if check(mid):  # 检查中点是否可行
                l = mid  # 可行则保留 mid，继续向右找更大的
            else:  # 否则中点不可行
                r = mid - 1  # 不可行则区间右端左缩
        return l  # 返回收敛后的最大可行频数
