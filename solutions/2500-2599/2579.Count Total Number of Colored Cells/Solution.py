# 题目：2579. 统计染色格子数（Count Total Number of Colored Cells）
# 思路：第 i 圈新增 4(i-1) 个格子，逐圈累加后通项为 2n(n-1)+1，直接套公式。
# 时间复杂度：O(1)，一次乘加；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def coloredCells(self, n: int) -> int:  # n 表示第几圈，返回染色格子总数
        return 2 * n * (n - 1) + 1  # 新增格子数依次为 0、4、8…，累加得 2n(n-1)+1；Python 整数不会溢出，直接算即可
