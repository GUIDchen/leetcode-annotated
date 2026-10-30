# 题目：52. N 皇后 II（N-Queens II）
# 思路：逐行深搜 + 回溯，只统计方案数。用三个布尔数组标记列、副对角线（i+j）、主对角线（i-j+n）的占用情况。
# 时间复杂度：O(n!)，回溯树的规模；空间复杂度：O(1)，标记数组与递归栈都是常数级。
class Solution:  # LeetCode 约定的题解类
    def totalNQueens(self, n: int) -> int:  # n 为棋盘边长，返回合法布局的个数
        def dfs(i: int):  # 深搜第 i 行；作为闭包直接读写外部的 cols / dg / udg / ans
            if i == n:  # 所有行都放完了，说明找到一个合法布局
                nonlocal ans  # 声明 ans 是外层函数作用域的变量，才能在这里修改它
                ans += 1  # 方案数加一
                return  # 回到上一层继续尝试
            for j in range(n):  # 枚举第 i 行皇后所在的列 j
                a, b = i + j, i - j + n  # a 为副对角线编号，b 为加偏移后的主对角线编号
                if cols[j] or dg[a] or udg[b]:  # 任一方向已被占用，则这个位置不能放
                    continue  # 跳过该列，继续试下一个位置
                cols[j] = dg[a] = udg[b] = True  # 占用当前列与两条对角线
                dfs(i + 1)  # 递归处理下一行
                cols[j] = dg[a] = udg[b] = False  # 回溯：释放列与两条对角线的占用

        cols = [False] * 10  # 列占用标记；n ≤ 9，固定开 10 个位置
        dg = [False] * 20  # 副对角线占用标记，最多 2n-1 ≤ 17 条
        udg = [False] * 20  # 主对角线占用标记，下标 i - j + n 偏移 n 后非负
        ans = 0  # 合法布局计数器
        dfs(0)  # 从第 0 行开始搜索
        return ans  # 返回方案总数
