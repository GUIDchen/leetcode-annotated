# 题目：1594. 矩阵的最大非负积（Maximum Non Negative Product in a Matrix）
# 思路：路径乘积的符号只由正负决定，逐格同时维护「最小积」与「最大积」，乘法时交叉取极值。
# 时间复杂度：O(m * n)，每个格子只转移一次；空间复杂度：O(m * n)，保存每个格子的最小积与最大积。
class Solution:  # LeetCode 约定的题解类
    def maxProductPath(self, grid: List[List[int]]) -> int:  # grid 为 m 行 n 列、元素可正可负的矩阵
        m, n = len(grid), len(grid[0])  # 分别取行数与列数
        f = [[[0, 0] for _ in range(n)] for _ in range(m)]  # f[i][j] = [最小积, 最大积]，保存到达格子 (i, j) 的两种极值

        # 按行、列顺序做二维动态规划
        for i in range(m):  # 枚举行
            for j in range(n):  # 枚举列
                x = grid[i][j]  # 当前格子的值
                if i == 0 and j == 0:  # 左上角起点，没有前驱格子
                    f[i][j][0] = x  # 起点的最小积等于自身
                    f[i][j][1] = x  # 起点的最大积也等于自身
                    continue  # 起点处理完，跳过后面的转移

                # 用正负无穷初始化，后面统一用 min/max 收敛
                mn, mx = inf, -inf  # 最小积与最大积的临时变量，先取正负无穷

                # 从上方格子转移
                if i > 0:  # 存在上方格子
                    a, b = f[i - 1][j]  # a 取最小积，b 取最大积
                    mn = min(mn, a * x, b * x)  # 乘以当前值可能反号，最小值取两种乘积的较小者
                    mx = max(mx, a * x, b * x)  # 最大值取两种乘积中的较大者

                # 从左侧格子转移
                if j > 0:  # 存在左侧格子
                    a, b = f[i][j - 1]  # 取左侧格子的最小积与最大积
                    mn = min(mn, a * x, b * x)  # 用左侧转移结果更新最小值
                    mx = max(mx, a * x, b * x)  # 用左侧转移结果更新最大值

                # 两类前驱都算完，写入当前格子的最终结果
                f[i][j][0], f[i][j][1] = mn, mx  # 同时写入最小积与最大积

        # 右下角的最大积就是答案
        ans = f[m - 1][n - 1][1]  # 取出右下角的最大积作为候选答案
        mod = 10**9 + 7  # 题目要求的取模常量
        return -1 if ans < 0 else ans % mod  # 负数说明不存在非负积，否则取模后返回
