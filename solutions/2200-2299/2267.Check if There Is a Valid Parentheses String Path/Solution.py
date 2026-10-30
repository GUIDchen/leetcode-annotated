# 题目：2267. 检查是否有合法括号字符串路径（Check if There Is a Valid Parentheses String Path）
# 思路：DFS 加记忆化（@cache）。状态 (i, j, k) 表示到达 (i, j) 时的净左括号数 k；k 不能为负且不能超过剩余格子数，走到终点时 k == 0 才合法。
# 时间复杂度：O(m * n * (m + n))，即被缓存的状态总数；空间复杂度：O(m * n * (m + n))，用于缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def hasValidPath(self, grid: List[List[str]]) -> bool:  # grid：由 '(' 与 ')' 组成的网格
        @cache  # 记忆化装饰器：相同的 (i, j, k) 只真正计算一次
        def dfs(i: int, j: int, k: int) -> bool:  # 从 (i, j) 出发、当前净左括号数为 k，能否走到终点并正确匹配
            d = 1 if grid[i][j] == "(" else -1  # 当前格子的贡献：'(' 记为 +1，')' 记为 -1
            k += d  # 把当前格子的括号计入净左括号数
            if k < 0 or k > m - i + n - j:  # 净数不能为负；也不能超过剩余格子数，否则后面无法回到 0
                return False  # 剪枝：该分支一定凑不出合法括号串
            if i == m - 1 and j == n - 1:  # 已经到达右下角终点
                return k == 0  # 净数为 0 说明括号恰好完全匹配
            for a, b in pairwise((0, 1, 0)):  # pairwise 把 (0,1,0) 两两配对，依次得到向下 (0,1) 与向右 (1,0)
                x, y = i + a, j + b  # 计算下一个格子的坐标
                if 0 <= x < m and 0 <= y < n and dfs(x, y, k):  # 坐标在界内，且该方向能找到合法路径
                    return True  # 只要存在一条合法路径就立即返回成功
            return False  # 两个方向都走不通，本状态失败

        m, n = len(grid), len(grid[0])  # 网格行列数；必须先于 dfs 的调用赋值，dfs 内部通过闭包读取
        if (m + n - 1) % 2 or grid[0][0] == ")" or grid[m - 1][n - 1] == "(":  # 路径长度必须为偶数；起点不能是 ')'；终点不能是 '('
            return False  # 任一前提不满足，直接判定不存在合法路径
        return dfs(0, 0, 0)  # 从左上角出发，初始净左括号数为 0
