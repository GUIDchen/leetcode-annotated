# 题目：1931. 用三种不同颜色为网格涂色（Painting a Grid With Three Different Colors）
# 思路：把每列压成三进制编码，筛出列内合法编码并两两判断能否相邻，再逐列做转移计数 DP。
# 时间复杂度：O(n·9^m)，合法编码至多 3^m 个；空间复杂度：O(3^m + 转移边数)。
class Solution:  # LeetCode 约定的题解类
    def colorTheGrid(self, m: int, n: int) -> int:  # m 行 n 列，返回合法涂色方案数
        def f1(x: int) -> bool:  # 判断单列编码 x 是否满足列内相邻格子颜色不同
            last = -1  # 上一个格子的颜色，-1 表示还没有
            for _ in range(m):  # 逐行检查，每行对应三进制的一位
                if x % 3 == last:  # 当前位颜色与上一位相同，则该列不合法
                    return False  # 提前返回不合法
                last = x % 3  # 更新「上一个颜色」
                x //= 3  # 右移一位三进制，处理下一行
            return True  # 列内相邻颜色都不同

        def f2(x: int, y: int) -> bool:  # 判断相邻两列编码 x、y 是否没有同一行同色
            for _ in range(m):  # 逐行比较两列的颜色
                if x % 3 == y % 3:  # 同一行颜色相同，两列无法相邻
                    return False  # 提前返回不可相邻
                x, y = x // 3, y // 3  # 同时右移 x、y 的三进制位
            return True  # 每一行颜色都不同，可以相邻

        mod = 10**9 + 7  # 取模常量
        mx = 3**m  # 一列的所有编码数量：3^m
        valid = {i for i in range(mx) if f1(i)}  # 集合推导：所有自身合法的列编码
        d = defaultdict(list)  # 邻接表：d[x] 保存所有可以与列 x 相邻的列编码
        for x in valid:  # 枚举左列编码
            for y in valid:  # 枚举右列编码
                if f2(x, y):  # 两列在每一行都不同色，可以相邻
                    d[x].append(y)  # 记录一条转移边 x -> y
        f = [int(i in valid) for i in range(mx)]  # DP 初值：第一列每种合法编码各 1 种方案
        for _ in range(n - 1):  # 逐列递推 n-1 次
            g = [0] * mx  # 下一层的 DP 数组
            for i in valid:  # 枚举当前列编码
                for j in d[i]:  # 枚举可以转移到它的上一列编码
                    g[i] = (g[i] + f[j]) % mod  # 累加方案数并取模
            f = g  # 滚动：把下一层当作当前层
        return sum(f) % mod  # 汇总最后一列所有方案数并取模
