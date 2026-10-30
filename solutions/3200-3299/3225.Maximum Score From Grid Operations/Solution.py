# 题目：3225. 网格图操作后的最大分数（Maximum Score From Grid Operations）
# 思路：用 k[j] 表示第 j 列染黑的高度，第 j 列贡献 max(0, s[j][max(k[j-1],k[j+1])] - s[j][k[j]])，按列做 DP，并用前缀/后缀最大值把每层转移从 O(n^2) 降到 O(n)。
# 时间复杂度：O(n^3)，n 层状态 × O(n^2) 转移；空间复杂度：O(n^2)，存列前缀和与两层 DP 表。
class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, grid: List[List[int]]) -> int:  # grid：n x n 网格；返回操作后能得到的最大总分
        n = len(grid)  # 网格边长
        s = [[0] * (n + 1) for _ in range(n)]  # s[j][h]：第 j 列前 h 个格子的前缀和
        for j in range(n):  # 逐列做预处理
            for i, x in enumerate(grid):  # 沿列扫描每一行（x 是整行，取它的第 j 列）
                s[j][i + 1] = s[j][i] + x[j]  # 累加当前行得到第 j 列的前缀和
        f = [[-inf] * (n + 1) for _ in range(n + 1)]  # f[h1][h2]：当前列高 h1、前一列高 h2 时的最大得分（-inf 表示不可达，inf 由判题环境提供）
        for h in range(n + 1):  # 第 0 列左边没有列，前一列高度按 0 处理
            f[h][0] = 0  # 高度为 h 的第 0 列此时得分为 0
        for j in range(n - 1):  # 逐列向右转移，每轮固定第 j 列
            g = [[-inf] * (n + 1) for _ in range(n + 1)]  # 下一层状态 g[下一列高度 hp][当前列高度 h1]
            for h1 in range(n + 1):  # 枚举当前列高度 h1（即 k[j]）
                pre = [-inf] * (n + 2)  # 前缀最大值数组，多开一位作哨兵
                pre[0] = f[h1][0]  # 前缀最大值的起点
                for h2 in range(1, n + 1):  # 从左往右构建 h2 的前缀最大值
                    pre[h2] = max(pre[h2 - 1], f[h1][h2])  # pre[h2] = max(f[h1][0..h2])
                suf = [-inf] * (n + 2)  # 后缀最大值数组，多开一位作哨兵
                for h2 in range(n, -1, -1):  # 从右往左构建 h2 的后缀最大值
                    v = -inf  # 不可达状态的哨兵值
                    if f[h1][h2] != -inf:  # 只对可达状态计算候选值
                        v = f[h1][h2] + max(0, s[j][h2] - s[j][h1])  # max(h2,hp)=h2 分支：加上当前列多出来的白格前缀和
                    suf[h2] = max(suf[h2 + 1], v)  # suf[h2] = max_{h2' >= h2}（f[h1][h2'] + 加成）
                for hp in range(n + 1):  # 枚举下一列（第 j+1 列）的高度 hp
                    add = max(0, s[j][hp] - s[j][h1])  # 下一列更高时，当前列高出的白格也能计分
                    v1 = -inf if pre[hp] == -inf else pre[hp] + add  # h2 <= hp 时用前缀最大值转移
                    g[hp][h1] = max(v1, suf[hp + 1])  # h2 > hp 时加成已在 suf 中，两部分取大即最优
            f = g  # 滚动更新：g 成为下一轮的当前状态
        ans = 0  # 最后一列没有右邻居，总分至少为 0
        for h1 in range(n + 1):  # 枚举最后一列高度 h1（即 k[n-1]）
            for h2 in range(n + 1):  # 枚举倒数第二列高度 h2（即 k[n-2]）
                if f[h1][h2] != -inf:  # 跳过不可达状态
                    ans = max(ans, f[h1][h2] + max(0, s[-1][h2] - s[-1][h1]))  # 补上最后一列只受左邻居影响的贡献
        return ans  # 返回最大总分
