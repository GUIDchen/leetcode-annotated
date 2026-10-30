# 题目：51. N 皇后（N-Queens）
# 思路：逐行深搜 + 回溯。用三个数组分别标记列、副对角线（i+j）、主对角线（n-i+j）是否被占用，每行放一个皇后，冲突就剪枝。
# 时间复杂度：O(n!)，回溯树的规模；空间复杂度：O(n)，递归栈与三个标记数组（不含存放答案的空间）。
class Solution:  # LeetCode 约定的题解类
    def solveNQueens(self, n: int) -> List[List[str]]:  # n 为棋盘边长，返回所有合法布局（每个布局是字符串列表）
        def dfs(i: int):  # 深搜第 i 行；作为闭包直接读写外部的 g / col / dg / udg / ans
            if i == n:  # n 行都放好了，说明拿到一个合法解
                ans.append(["".join(row) for row in g])  # 把字符矩阵的每一行拼成字符串后整体存入答案
                return  # 本分支结束，回溯到上一层
            for j in range(n):  # 尝试把第 i 行的皇后放在第 j 列
                if col[j] + dg[i + j] + udg[n - i + j] == 0:  # 列与两条对角线都空闲才可落子（三者都为 0）
                    g[i][j] = "Q"  # 落子：在棋盘上标记皇后
                    col[j] = dg[i + j] = udg[n - i + j] = 1  # 同时标记该列与两条对角线被占用
                    dfs(i + 1)  # 递归处理下一行
                    col[j] = dg[i + j] = udg[n - i + j] = 0  # 回溯：撤销该列与两条对角线的占用
                    g[i][j] = "."  # 回溯：把皇后从棋盘上拿掉

        ans = []  # 保存所有合法布局
        g = [["."] * n for _ in range(n)]  # n×n 棋盘，初始全是 '.'
        col = [0] * n  # col[j] 标记第 j 列是否被占用
        dg = [0] * (n << 1)  # 副对角线占用标记，下标 i + j，共 2n-1 条
        udg = [0] * (n << 1)  # 主对角线占用标记，下标 n - i + j，偏移 n 避免负数
        dfs(0)  # 从第 0 行开始搜索
        return ans  # 返回所有合法布局
