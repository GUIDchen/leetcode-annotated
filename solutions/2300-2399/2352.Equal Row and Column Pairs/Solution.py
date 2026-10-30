# 题目：2352. 相等行列对（Equal Row and Column Pairs）
# 思路：枚举每个 (行 i, 列 j)，用 all 判断第 i 行与第 j 列是否逐元素全等，相等就让答案加一。
# 时间复杂度：O(n^3)，两重枚举加一次 all 比较；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def equalPairs(self, grid: List[List[int]]) -> int:  # grid：n × n 的整数矩阵
        n = len(grid)  # 矩阵的边长
        ans = 0  # 相等行列对的计数
        for i in range(n):  # 枚举行下标 i
            for j in range(n):  # 枚举列下标 j
                ans += all(grid[i][k] == grid[k][j] for k in range(n))  # 逐元素全等时 all 为 True，等价于答案加一
        return ans  # 返回相等行列对的总数
