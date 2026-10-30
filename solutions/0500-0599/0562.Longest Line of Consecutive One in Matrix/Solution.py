# 题目：562. 矩阵中最长的连续 1 线段（Longest Line of Consecutive One in Matrix）
# 思路：四个方向分别做线性 DP：a/b/c/d 记录以当前格为终点在该方向上的连续 1 长度，边填表边更新最大值。
# 时间复杂度：O(m·n)；空间复杂度：O(m·n)，四个 DP 表（均外扩一圈 0 边界）。
class Solution:  # LeetCode 约定的题解类
    def longestLine(self, mat: List[List[int]]) -> int:  # mat 是只含 0/1 的矩阵，返回八个方向中最长的连续 1 线段长度
        m, n = len(mat), len(mat[0])  # m、n 分别是行数与列数
        a = [[0] * (n + 2) for _ in range(m + 2)]  # a[i][j]：以 (i,j) 为终点、竖直方向的连续 1 长度；多一行一列 0 边界
        b = [[0] * (n + 2) for _ in range(m + 2)]  # b[i][j]：以 (i,j) 为终点、水平方向的连续 1 长度
        c = [[0] * (n + 2) for _ in range(m + 2)]  # c[i][j]：以 (i,j) 为终点、主对角线方向的连续 1 长度
        d = [[0] * (n + 2) for _ in range(m + 2)]  # d[i][j]：以 (i,j) 为终点、副对角线方向的连续 1 长度
        ans = 0  # ans 记录所有方向上的最大长度
        for i in range(1, m + 1):  # 从 1 开始遍历，靠外扩的一圈 0 边界避免下标越界
            for j in range(1, n + 1):  # j 同样从 1 开始，对应原矩阵第 j-1 列
                if mat[i - 1][j - 1]:  # 只有当前位置是 1 才可能延长线段
                    a[i][j] = a[i - 1][j] + 1  # 竖直方向的长度 = 上一行同列 + 1
                    b[i][j] = b[i][j - 1] + 1  # 水平方向的长度 = 同一行左一列 + 1
                    c[i][j] = c[i - 1][j - 1] + 1  # 主对角线方向的长度 = 左上角 + 1
                    d[i][j] = d[i - 1][j + 1] + 1  # 副对角线方向的长度 = 右上角（j+1 列）+ 1，因此每行要多开两列
                    ans = max(ans, a[i][j], b[i][j], c[i][j], d[i][j])  # 四个方向取最大值，再更新答案
        return ans  # 返回最长连续 1 线段的长度
