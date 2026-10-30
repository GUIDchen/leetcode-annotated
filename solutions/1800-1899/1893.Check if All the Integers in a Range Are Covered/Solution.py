# 题目：1893. 检查是否区域内所有整数都被覆盖（Check if All the Integers in a Range Are Covered）
# 思路：差分数组标记每个区间的起止，前缀和得到每个整数的覆盖次数；[left, right] 内出现覆盖数为 0 的点即返回 False。
# 时间复杂度：O(n + 50)，n 为区间个数；空间复杂度：O(50)，差分数组长度固定为 52。
class Solution:  # LeetCode 约定的题解类
    def isCovered(self, ranges: List[List[int]], left: int, right: int) -> bool:  # ranges：给定区间集合；left、right：待检查的目标区间（数值范围 1..50）
        diff = [0] * 52  # 差分数组，长度 52 覆盖 1..50 的端点及其 +1
        for l, r in ranges:  # 逐个区间做差分标记
            diff[l] += 1  # 区间起点 +1
            diff[r + 1] -= 1  # 终点后一位 -1；r + 1 最大 51，不会越界
        s = 0  # 前缀和变量，表示当前下标的覆盖次数
        for i, x in enumerate(diff):  # enumerate 同时取下标 i 与差分值 x
            s += x  # 累加差分值，得到 i 处的覆盖次数
            if s <= 0 and left <= i <= right:  # 覆盖数为 0 且该点在目标区间内，说明没被完全覆盖
                return False  # 提前返回 False
        return True  # 目标区间内每个点都被覆盖
