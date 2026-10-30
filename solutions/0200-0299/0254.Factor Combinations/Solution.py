# 题目：254. 因子的组合（Factor Combinations）
# 思路：回溯。dfs(n, i) 表示剩余待分解的数 n 与因子下界 i，先把「当前路径 + [n]」记为一个解，再从 i 枚举到 sqrt(n) 继续分解。
# 时间复杂度：与解的个数、每个解的长度成正比；空间复杂度：O(log n)，递归深度等于因子个数。

class Solution:  # LeetCode 约定的题解类
    def getFactors(self, n: int) -> List[List[int]]:  # n：待分解的正整数
        def dfs(n, i):  # 内层递归：n 为剩余待分解的数，i 为下一个因子的下界
            if t:  # 路径非空时，剩余的数 n 可以单独作为最后一个因子
                ans.append(t + [n])  # 用 t + [n] 生成新列表，既拼出完整组合又不修改 t
            j = i  # 因子 j 从下界 i 开始枚举
            while j * j <= n:  # 只需枚举到 sqrt(n)，更大的因子会与更小的因子重复
                if n % j == 0:  # j 能整除 n 才是合法因子
                    t.append(j)  # 选中因子 j，压入路径
                    dfs(n // j, j)  # 继续分解 n // j，下界设为 j 保证因子非递减
                    t.pop()  # 回溯：撤销选择
                j += 1  # 尝试下一个因子

        t = []  # 回溯路径：已选定的因子
        ans = []  # 结果集：所有合法的因子组合
        dfs(n, 2)  # 从 n 开始分解，因子最小为 2
        return ans  # 返回所有因子组合
