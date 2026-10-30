# 题目：3240. 最少翻转次数使二进制矩阵回文 II（Minimum Number of Flips to Make Binary Grid Palindromic II）
# 思路：同时满足行回文与列回文，先把每组四个对称格子凑成相同值；再单独处理中间行/列，并让 1 的总个数是 4 的倍数。
# 时间复杂度：O(m × n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def minFlips(self, grid: List[List[int]]) -> int:  # grid 是 0/1 矩阵，返回最少翻转次数
        m, n = len(grid), len(grid[0])  # m 行数，n 列数
        ans = 0  # ans 累计需要翻转的次数
        for i in range(m // 2):  # 枚举左上四分之一区域
            for j in range(n // 2):  # 每个格子代表一组 4 个互相约束的对称位置
                x, y = m - i - 1, n - j - 1  # 这一组中右下对称格子的坐标
                cnt1 = grid[i][j] + grid[x][j] + grid[i][y] + grid[x][y]  # 四个对称位置上 1 的个数
                ans += min(cnt1, 4 - cnt1)  # 全变 0 要翻 cnt1 次，全变 1 要翻 4-cnt1 次，取较小
        if m % 2 and n % 2:  # 行列都是奇数时，正中间一格自成一且唯一的组
            ans += grid[m // 2][n // 2]  # 孤立的一格必须变成 0，否则 1 的个数除不尽 4
        # 下面单独处理中间行与中间列：这两条线上的格子不属于任何四元组
        diff = cnt1 = 0  # diff：中间行/列里两数不同、必翻一次的组数；cnt1：已是 11 的组贡献的 1 的个数
        if m % 2:  # 行数为奇数时处理中间行
            for j in range(n // 2):  # 中间行左半部分与右半部分配对
                if grid[m // 2][j] == grid[m // 2][n - j - 1]:  # 配对的两个数相同，可一起变 0 或一起变 1
                    cnt1 += grid[m // 2][j] * 2  # 都是 1 时这一对贡献 2 个 1
                else:  # 两个数不同：必须翻一个，翻完只剩奇数个 1
                    diff += 1  # 记一个「必翻一次」的组
        if n % 2:  # 列数为奇数时处理中间列，逻辑同上
            for i in range(m // 2):  # 中间列上半部分与下半部分配对
                if grid[i][n // 2] == grid[m - i - 1][n // 2]:  # 配对的两个数相同
                    cnt1 += grid[i][n // 2] * 2  # 都是 1 时贡献 2 个 1
                else:  # 两个数不同，必须翻一个
                    diff += 1  # 记一个必翻一次的组
        ans += diff if cnt1 % 4 == 0 or diff else 2  # 已有 1 的个数是 4 的倍数，或有 diff 组可调节，就只加 diff；否则额外翻 2 次
        return ans  # 返回最少翻转次数
