# 题目：2226. 每个小孩最多能分到多少糖果（Maximum Candies Allocated to K Children）
# 思路：二分答案。每人分 x 颗可行则分更少也一定可行，答案有单调性；用堆大小整除 x 求和得到可切份数，份数达到 k 即说明 x 可行。
# 时间复杂度：O(n log C)，n 为堆数、C 为最大堆大小，每轮二分用生成器 O(n) 求和；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumCandies(self, candies: List[int], k: int) -> int:  # candies：每堆的糖果数；k：小孩人数
        l, r = 0, max(candies)  # 二分区间 [l, r]：0 一定可行，最大堆大小是答案上界
        while l < r:  # 区间尚未收缩到单点，继续二分
            mid = (l + r + 1) >> 1  # 上取整的中点，配合后面的 l = mid 避免死循环
            if sum(x // mid for x in candies) >= k:  # 每堆能切出 x // mid 份，总份数达到 k 说明 mid 可行
                l = mid  # 可行则保留 mid，把区间下界抬到 mid，继续找更大的值
            else:  # 份数不够，mid 偏大
                r = mid - 1  # 答案至多为 mid - 1
        return l  # 区间收缩到单点即为可行的最大值
