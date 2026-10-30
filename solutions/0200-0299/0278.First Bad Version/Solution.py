# 题目：278. 第一个错误的版本（First Bad Version）
# 思路：答案具有单调性，用二分查找最小的坏版本；mid 为坏则收缩右界，否则左界右移跳过 mid。
# 时间复杂度：O(log n)，区间每次折半；空间复杂度：O(1)，只用了常数个变量。
# The isBadVersion API is already defined for you.
# def isBadVersion(version: int) -> bool:


class Solution:  # LeetCode 约定的题解类
    def firstBadVersion(self, n: int) -> int:  # n 是版本总数，返回第一个坏版本的版本号
        l, r = 1, n  # 二分区间 [l, r]，初始覆盖 1..n
        while l < r:  # 区间还没收缩成单点，继续二分
            mid = (l + r) >> 1  # 取中点；右移一位等价于整除 2
            if isBadVersion(mid):  # 中点是坏版本，答案不会超过 mid
                r = mid  # 右界收缩到 mid，把 mid 留作候选
            else:  # 中点是正常版本
                l = mid + 1  # 左界跳过 mid，答案在 mid 之后
        return l  # 区间收敛成一点，即第一个坏版本
