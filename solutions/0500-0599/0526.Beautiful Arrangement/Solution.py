# 题目：526. 优美的排列（Beautiful Arrangement）
# 思路：DFS 回溯，为位置 1..n 依次选数，选中的数必须能被位置整除或整除位置；预处理可选集合剪枝。
# 时间复杂度：O(n!)，最坏枚举全部排列（剪枝后远小于此）；空间复杂度：O(n²)，match 表与访问数组。
class Solution:  # LeetCode 约定的题解类
    def countArrangement(self, n: int) -> int:  # n：排列规模；返回 1..n 的优美排列个数
        def dfs(i):  # 内层 DFS：为位置 i 选择一个还没用过的数字
            nonlocal ans, n  # 声明外层变量，dfs 内要修改 ans 并读取 n
            if i == n + 1:  # i 走到 n+1 说明 1..n 已经全部放好
                ans += 1  # 方案数加一
                return  # 回溯到上一层，继续尝试其它数字
            for j in match[i]:  # 遍历位置 i 的所有合法候选数字
                if not vis[j]:  # 只尝试还没被使用的数字
                    vis[j] = True  # 标记 j 已被使用
                    dfs(i + 1)  # 递归填下一个位置
                    vis[j] = False  # 回溯：撤销标记，恢复现场

        ans = 0  # 合法排列的计数器
        vis = [False] * (n + 1)  # 访问数组，下标 1..n 对应数字 1..n
        match = defaultdict(list)  # match[i] 存放可以放在位置 i 上的数字
        for i in range(1, n + 1):  # 枚举每个位置 i
            for j in range(1, n + 1):  # 枚举可能放在该位置的数值 j
                if j % i == 0 or i % j == 0:  # 满足「位置整除数字」或「数字整除位置」即可
                    match[i].append(j)  # 把 j 收进位置 i 的候选集合

        dfs(1)  # 从位置 1 开始深度优先搜索
        return ans  # 返回方案总数
