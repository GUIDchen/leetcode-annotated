# 题目：598. 区间加法 II（Range Addition II）
# 思路：每个操作都从左上角 (0,0) 开始加一，所以最大值一定出现在所有操作的公共矩形内，其大小等于最小行范围乘以最小列范围。
# 时间复杂度：O(k)，k 为 ops 长度；空间复杂度：O(1)，只更新 m、n 两个变量。
class Solution:  # LeetCode 约定的题解类
    def maxCount(self, m: int, n: int, ops: List[List[int]]) -> int:  # m、n 是矩阵行列数，ops 是若干次矩形加一操作
        for a, b in ops:  # 逐个枚举操作，把公共矩形收窄到最小的行数与列数
            m = min(m, a)  # 该操作覆盖前 a 行，所以可覆盖行数取两者较小值
            n = min(n, b)  # 列方向同理，取所有操作列范围的最小值
        return m * n  # 公共矩形的格子数就是被加次数最多的格子个数
