# 题目：1033. 移动石子直到连续（Moving Stones Until Consecutive）
# 思路：定位最左、中间、最右三颗石子；跨度为 2 时已连续（0 步），否则最小步数看有没有长度 <3 的空隙（1 步），最大步数是空位总数。
# 时间复杂度：O(1)，常数次比较；空间复杂度：O(1)，只使用几个整型变量。
class Solution:  # LeetCode 约定的题解类
    def numMovesStones(self, a: int, b: int, c: int) -> List[int]:  # 返回 [最小移动次数, 最大移动次数]；每步只能把端点石子移到空位且保持有序
        x, z = min(a, b, c), max(a, b, c)  # 一次求出最小值 x 与最大值 z
        y = a + b + c - x - z  # 中间那颗石子的位置：三数之和减去首尾
        mi = mx = 0  # mi 最小移动次数、mx 最大移动次数，已经连续时都保持 0
        if z - x > 2:  # 首尾跨度大于 2 说明还没连成连续三颗
            mi = 1 if y - x < 3 or z - y < 3 else 2  # 任一段空隙小于 3 时可以一步补上，否则至少两步
            mx = z - x - 2  # 最大步数等于跨度内的空位个数 z-x-2
        return [mi, mx]  # 返回 [最小移动次数, 最大移动次数]
