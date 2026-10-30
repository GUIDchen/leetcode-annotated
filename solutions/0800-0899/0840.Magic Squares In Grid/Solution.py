# 题目：840. 矩阵中的幻方（Magic Squares In Grid）
# 思路：枚举每个 3×3 子矩阵，检查数字是否恰为 1..9 且互不重复、两条对角线和相等、三行三列之和都与之相等；满足即是 3 阶幻方。
# 时间复杂度：O(m·n)，每个位置只检查常数大小的 3×3 子矩阵；空间复杂度：O(1)，只用到集合与长度 3 的数组。
class Solution:  # LeetCode 约定的题解类
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:  # grid 是 m×n 矩阵，返回其中 3×3 幻方的个数
        def check(i: int, j: int) -> int:  # 内部函数：判断以 (i,j) 为左上角的 3×3 子矩阵是否为幻方，是返回 1，否则 0
            if i + 3 > m or j + 3 > n:  # 子矩阵越出矩阵边界
                return 0  # 直接判定不是幻方
            s = set()  # 收集子矩阵中的 9 个数字，用于判重
            row = [0] * 3  # 三行各自的和
            col = [0] * 3  # 三列各自的和
            a = b = 0  # a 是主对角线之和，b 是副对角线之和
            for x in range(i, i + 3):  # 遍历子矩阵的行
                for y in range(j, j + 3):  # 遍历子矩阵的列
                    v = grid[x][y]  # 当前格子的值
                    if v < 1 or v > 9:  # 数字必须落在 1..9
                        return 0  # 违反则不是幻方
                    s.add(v)  # 把数字加入集合，重复时集合大小会小于 9
                    row[x - i] += v  # 累加到所在行
                    col[y - j] += v  # 累加到所在列
                    if x - i == y - j:  # 相对行号等于相对列号，落在主对角线上
                        a += v  # 累加主对角线之和
                    if x - i == 2 - (y - j):  # 相对行号与相对列号之和为 2，落在副对角线上
                        b += v  # 累加副对角线之和
            if len(s) != 9 or a != b:  # 9 个数字必须互不相同，且两条对角线和相等
                return 0  # 否则不是幻方
            if any(x != a for x in row) or any(x != a for x in col):  # 每一行、每一列之和都必须等于对角线和
                return 0  # 否则不是幻方
            return 1  # 全部条件满足，是幻方

        m, n = len(grid), len(grid[0])  # 矩阵的行数与列数（供内部函数闭包使用）
        return sum(check(i, j) for i in range(m) for j in range(n))  # 枚举所有左上角，累加是幻方的个数
