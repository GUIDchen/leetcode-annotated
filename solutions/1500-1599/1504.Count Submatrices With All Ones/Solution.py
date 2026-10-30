# 题目：1504. 统计全 1 子矩形（Count Submatrices With All Ones）
# 思路：先求 g[i][j] = 以 (i,j) 结尾向左连续 1 的个数；再枚举右下角 (i,j)，向上扩展高度，累加该高度下的最小宽度。
# 时间复杂度：O(m^2 * n)，枚举底边、右边、顶边三层；空间复杂度：O(m * n)，保存连续 1 长度表。
class Solution:  # LeetCode 约定的题解类
    def numSubmat(self, mat: List[List[int]]) -> int:  # mat：0/1 矩阵；返回所有元素全为 1 的子矩形个数
        m, n = len(mat), len(mat[0])  # m 行 n 列
        g = [[0] * n for _ in range(m)]  # g[i][j]：以 (i,j) 为右端向左连续 1 的个数，0 表示该格本身为 0
        for i in range(m):  # 逐行扫描
            for j in range(n):  # 逐列扫描
                if mat[i][j]:  # 当前格为 1 时才需要统计
                    g[i][j] = 1 if j == 0 else 1 + g[i][j - 1]  # 第 0 列为 1；否则等于左边一格的值加 1
        ans = 0  # 全 1 子矩形的个数累加器
        for i in range(m):  # 枚举子矩形的底边所在行 i
            for j in range(n):  # 枚举子矩形的右边所在列 j
                col = inf  # 自底向上扩展时的最小宽度，inf 表示无穷大作为初值
                for k in range(i, -1, -1):  # 顶边 k 从 i 逐行上移到 0
                    col = min(col, g[k][j])  # 高度增加一行，宽度取覆盖到的各行左连续长度的最小值
                    ans += col  # 该高度下左边界的可选位置有 col 个，全部计入答案
        return ans  # 返回全 1 子矩形总数
