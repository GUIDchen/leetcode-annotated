# 3432. Count Partitions with Even Sum Difference / 3432. 统计元素和差值为偶数的分区方案
# 核心思路：l 为左侧和、r 为右侧和，逐位移动分界并判断 (l - r) 是否为偶数。
# 复杂度：时间 O(n)，空间 O(1)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def countPartitions(self, nums: List[int]) -> int:  # 返回元素和差值为偶数的分区方案数
        l, r = 0, sum(nums)  # l 为左侧和，r 先取全部元素和，后续动态维护为右侧和
        ans = 0  # 记录满足条件的分区个数
        for x in nums[:-1]:  # 遍历除最后一个元素外的每个分区点
            l += x  # 把当前元素从右侧并入左侧
            r -= x  # 右侧和同步减去该元素
            ans += (l - r) % 2 == 0  # (l - r) 为偶数时该分区合法，布尔值可直接累加
        return ans  # 返回方案总数
