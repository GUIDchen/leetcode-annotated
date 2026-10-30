# 题目：1523. 在区间范围内统计奇数数目（Count Odd Numbers in an Interval Range）
# 核心思路：1..x 中的奇数个数是 (x+1)//2，用前缀差即得 [low, high] 内的奇数个数。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countOdds(self, low: int, high: int) -> int:  # low、high：闭区间的两个端点
        return ((high + 1) >> 1) - (low >> 1)  # >>1 等价于向下取整除 2：1..high 的奇数个数减去 1..low-1 的奇数个数
