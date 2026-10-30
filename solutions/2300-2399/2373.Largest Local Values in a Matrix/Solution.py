# 题目：2373. 矩阵中的局部最大值（Largest Local Values in a Matrix）
# 核心思路：对每个左上角 (i, j) 用生成器表达式扫过 3×3 窗口取最大值，填进尺寸为 (n-2)×(n-2) 的答案矩阵。
# 时间复杂度：O(n²)，共 (n-2)² 个窗口、每窗口固定 9 个元素；空间复杂度：O(n²)，存放答案矩阵。
class Solution:  # LeetCode 约定的题解类
    def largestLocal(self, grid: List[List[int]]) -> List[List[int]]:  # grid：n×n 的方阵，返回每个 3×3 子矩阵最大值组成的 (n-2)×(n-2) 矩阵
        n = len(grid)  # 矩阵边长 n，窗口左上角最多取到 n-3，所以答案维度是 n-2
        ans = [[0] * (n - 2) for _ in range(n - 2)]  # 预分配 (n-2)×(n-2) 的答案矩阵，每行独立建列表，避免别名共享
        for i in range(n - 2):  # 枚举每个窗口的左上角行号 i
            for j in range(n - 2):  # 枚举每个窗口的左上角列号 j
                ans[i][j] = max(  # 对当前位置的 3×3 窗口取最大值后写入答案矩阵
                    grid[x][y] for x in range(i, i + 3) for y in range(j, j + 3)  # 生成器表达式：行取 i..i+2、列取 j..j+2，正好覆盖整个 3×3 窗口
                )  # 生成器表达式结束（max 的参数括号在此闭合）
        return ans  # 返回每个 3×3 局部的最大值矩阵
