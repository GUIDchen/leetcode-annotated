# 题目：2679. 矩阵中的和（Sum in a Matrix）
# 思路：每轮取走各行当前最大值，得分是这些最大值中的最大者；每行排序后，第 j 轮的最大值就是各行的第 j 列，转置后逐列求最大值。
# 时间复杂度：O(m·n log n)，瓶颈是每行排序；空间复杂度：O(m)，zip 每列按需生成一个长度为 m 的元组。
class Solution:  # 每行排序后逐列取最大值求和
    def matrixSum(self, nums: List[List[int]]) -> int:  # nums 是 m 行 n 列的矩阵，返回各轮得分之和
        for row in nums:  # 逐行处理
            row.sort()  # 行内升序排序：之后这一行被取走的顺序就是从右往左的最大值
        return sum(map(max, zip(*nums)))  # zip(*nums) 按列转置，map(max) 取每列最大值（即每轮得分），sum 求和
