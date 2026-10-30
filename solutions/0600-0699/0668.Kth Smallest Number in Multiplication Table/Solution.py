# 题目：668. 乘法表中第 k 小的数（Kth Smallest Number in Multiplication Table）
# 思路：在 [1, m*n] 上二分答案，统计表中 ≤ mid 的个数；个数 ≥ k 则答案落在左半边，否则落在右半边。
# 时间复杂度：O(m log(mn))，每轮统计 O(m)、共 log(mn) 轮；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def findKthNumber(self, m: int, n: int, k: int) -> int:  # 返回 m × n 乘法表中第 k 小的数（非递减顺序计）
        left, right = 1, m * n  # 二分答案区间：最小 1，最大 m*n
        while left < right:  # 区间缩到一点时即为答案
            mid = (left + right) >> 1  # 取中点，右移一位等价于整除 2
            cnt = 0  # 统计表中 ≤ mid 的数字个数
            for i in range(1, m + 1):  # 遍历每一行
                cnt += min(mid // i, n)  # 第 i 行不超过 mid 的有 min(mid // i, n) 个，累加起来
            if cnt >= k:  # 个数已够 k 个，答案不会超过 mid
                right = mid  # 右界收窄
            else:  # 个数不足 k 个，答案一定大于 mid
                left = mid + 1  # 左界右移
        return left  # left == right 即第 k 小的数
