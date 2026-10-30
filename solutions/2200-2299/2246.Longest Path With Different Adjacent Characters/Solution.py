# 题目：2246. 相邻字符不同的最长路径（Longest Path With Different Adjacent Characters）
# 思路：树形 DP，dfs 返回以 i 为起点向下的最长合法单链；回溯时用「已记录的最长子链 + 当前子链」拼出过 i 的路径并更新 ans。
# 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(n)，邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def longestPath(self, parent: List[int], s: str) -> int:  # parent：每个结点的父结点；s：每个结点对应的字符
        def dfs(i: int) -> int:  # 返回以 i 为起点向下的最长「相邻字符不同」单链长度（单位是边）
            mx = 0  # mx：以 i 为顶点的最长合法单链，0 表示只取 i 自己
            nonlocal ans  # 声明 ans 来自外层函数，这样嵌套函数里才能修改它
            for j in g[i]:  # 遍历 i 的所有孩子
                x = dfs(j) + 1  # 孩子子树内的最长单链，加上边 (i, j) 这一条
                if s[i] != s[j]:  # 字符相同则这条边不能接，两段只能各自独立
                    ans = max(ans, mx + x)  # 用此前最长的另一条子链与当前子链拼成经过 i 的路径
                    mx = max(mx, x)  # 把当前子链纳入 mx，供后面的兄弟结点拼接时使用
            return mx  # 返回向下的最长单链给父结点

        g = defaultdict(list)  # 邻接表形式的树：g[u] 存放 u 的所有孩子
        for i in range(1, len(parent)):  # 根是 0，从下标 1 开始把每个结点挂到父亲下面
            g[parent[i]].append(i)  # 把子结点 i 加入 parent[i] 的孩子列表
        ans = 0  # 记录的是边数
        dfs(0)  # 从根结点开始 DFS
        return ans + 1  # 边数加 1 得到结点数（只有根时答案为 1）
