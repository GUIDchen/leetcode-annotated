# 题目：3212. 统计 X 和 Y 频数相等的子矩阵数量（Count Submatrices With Equal Frequency of X and Y）
# 思路：题目统计的是以 (0,0) 为左上角的子矩阵，用二维前缀和分别数出其中 X 与 Y 的个数，X 个数为正且等于 Y 个数时答案加一。
# 时间复杂度：O(mn)，每个格子常数次运算；空间复杂度：O(mn)，存放两通道前缀和。
class Solution:  # LeetCode 约定的题解类
    def numberOfSubmatrices(self, grid: List[List[str]]) -> int:  # grid：只含 'X'、'Y'、'.' 的字符矩阵
        m, n = len(grid), len(grid[0])  # m 行 n 列
        s = [[[0] * 2 for _ in range(n + 1)] for _ in range(m + 1)]  # 三维前缀和：s[i][j][0] / s[i][j][1] 分别是左上角到 (i,j) 区域内的 X / Y 个数
        ans = 0  # 满足条件的子矩阵计数
        for i, row in enumerate(grid, 1):  # 行下标从 1 开始，方便用 i-1 处理边界
            for j, x in enumerate(row, 1):  # 同时取得列下标 j 与当前字符 x
                s[i][j][0] = s[i - 1][j][0] + s[i][j - 1][0] - s[i - 1][j - 1][0]  # 二维前缀和容斥：上 + 左 - 左上
                s[i][j][1] = s[i - 1][j][1] + s[i][j - 1][1] - s[i - 1][j - 1][1]  # 同理统计 Y 的前缀和：上 + 左 - 左上
                if x != ".":  # 当前格不是空格才需要计入
                    s[i][j][ord(x) & 1] += 1  # ord('X') 为偶数、ord('Y') 为奇数，用 ASCII 奇偶直接选通道
                if s[i][j][0] > 0 and s[i][j][0] == s[i][j][1]:  # 以 (0,0) 为左上角、X 个数为正且与 Y 个数相等
                    ans += 1  # 该子矩阵符合条件，答案加一
        return ans  # 返回满足条件的子矩阵数量
