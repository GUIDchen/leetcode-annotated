# 题目：2428. 沙漏的最大总和（Maximum Sum of an Hourglass）
# 核心思路：枚举每个可能的沙漏中心，累加 3x3 方块后减去中间行左右两格，取最大值。
# 时间复杂度：O(m*n)，每个中心常数次求和；空间复杂度：O(1)，只用常数个临时变量。
class Solution:  # LeetCode 约定的题解类
    def maxSum(self, grid: List[List[int]]) -> int:  # grid 是输入矩阵，返回所有沙漏中的最大总和
        m, n = len(grid), len(grid[0])  # 同时取出行数 m 与列数 n
        ans = 0  # ans 记录最大沙漏总和；总和非负，初值 0 安全
        for i in range(1, m - 1):  # 中心行不能是首行或末行
            for j in range(1, n - 1):  # 中心列不能是首列或末列
                s = -grid[i][j - 1] - grid[i][j + 1]  # 先扣掉中间行左右两格，它们不属于沙漏形状
                s += sum(  # 再把 3x3 方形里的格子全部加回来
                    grid[x][y] for x in range(i - 1, i + 2) for y in range(j - 1, j + 2)  # 生成器表达式同时枚举三行三列，等价于双重循环累加
                )  # sum 的右括号结束，累加完成
                ans = max(ans, s)  # 用当前沙漏总和更新答案
        return ans  # 返回最大沙漏总和
