# 题目：1878. 矩阵中最大的三个菱形和（Get Biggest Three Rhombus Sums in a Grid）
# 思路：分别对「↘」与「↙」两个斜方向做前缀和，再枚举每个格子作为菱形中心与半径 k，用四条边的差分求和并修正多算/漏算的顶点，用 SortedSet 维护最大的三个和。
# 时间复杂度：O(m * n * min(m, n) * log 3)，枚举中心与半径；空间复杂度：O(m * n)，两张斜向前缀和表。
class Solution:  # LeetCode 约定的题解类
    def getBiggestThree(self, grid: List[List[int]]) -> List[int]:  # grid：m 行 n 列的正整数矩阵；返回最大的三个互不相同的菱形和（不足三个则全返回）
        m, n = len(grid), len(grid[0])  # m：行数；n：列数
        s1 = [[0] * (n + 2) for _ in range(m + 1)]  # s1[i][j]：沿「↘」方向到 (i, j) 的斜向前缀和；多开一行两列省去边界判断
        s2 = [[0] * (n + 2) for _ in range(m + 1)]  # s2[i][j]：沿「↙」方向到 (i, j) 的斜向前缀和；同样多留边界
        for i, row in enumerate(grid, 1):  # 用 1 基行号 i 遍历每一行 row（enumerate 的 start=1）
            for j, x in enumerate(row, 1):  # 用 1 基列号 j 遍历该行每个元素 x
                s1[i][j] = s1[i - 1][j - 1] + x  # 「↘」方向递推：左上格的前缀和再加当前格 x
                s2[i][j] = s2[i - 1][j + 1] + x  # 「↙」方向递推：右上格的前缀和再加当前格 x
        ss = SortedSet()  # SortedSet：自动去重且保持升序，方便随时取最小值和最后取最大的三个
        for i, row in enumerate(grid, 1):  # 枚举菱形的中心行 i（1 基）
            for j, x in enumerate(row, 1):  # 枚举菱形的中心列 j（1 基）
                l = min(i - 1, m - i, j - 1, n - j)  # 半径上限：中心到四条边界的最近距离，保证菱形不越界
                ss.add(x)  # 半径 0 的退化菱形就是单个格子，本身也是候选和
                for k in range(1, l + 1):  # 枚举半径 k，对应四边长度为 k 的菱形
                    a = s1[i + k][j] - s1[i][j - k]  # 左下边：沿「↘」从 (i, j-k) 到 (i+k, j) 的格子和
                    b = s1[i][j + k] - s1[i - k][j]  # 右上边：沿「↘」从 (i-k, j) 到 (i, j+k) 的格子和
                    c = s2[i][j - k] - s2[i - k][j]  # 左上边：沿「↙」从 (i-k, j) 到 (i, j-k) 的格子和
                    d = s2[i + k][j] - s2[i][j + k]  # 右下边：沿「↙」从 (i, j+k) 到 (i+k, j) 的格子和
                    ss.add(  # 调用 add 开始累加菱形和
                        a + b + c + d - grid[i + k - 1][j - 1] + grid[i - k - 1][j - 1]  # 四条边相加：下顶点被算两次要减掉，上顶点一次都没算要补上
                    )  # 调用结束，菱形和已插入有序集合
                while len(ss) > 3:  # 只要最大的三个和，多余的小值随时裁掉
                    ss.remove(ss[0])  # ss[0] 是最小元素，把它移除
        return list(ss)[::-1]  # 转成列表并反转，得到从大到小的最多三个菱形和
