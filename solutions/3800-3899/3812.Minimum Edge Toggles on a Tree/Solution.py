# 3812. Minimum Edge Toggles on a Tree | 翻转树上最少边
# 核心思路：自底向上 DFS，子树的字符与目标仍不一致时就必须翻转它与父亲之间那条边，并让父亲的标记取反；根节点仍不一致说明无解。
# 复杂度：时间 O(n log n)（DFS + 答案排序）；空间 O(n)（邻接表与递归栈）。
class Solution:  # 定义题解类
    def minimumFlips(  # 返回需要翻转的边下标（升序），无解时返回 [-1]（方法签名跨行）
        self, n: int, edges: List[List[int]], start: str, target: str  # 参数：点数 n、边列表 edges、初始字符串 start、目标字符串 target
    ) -> List[int]:  # 返回值为边下标列表
        g = [[] for _ in range(n)]  # 建 n 个空邻接表
        for i, (a, b) in enumerate(edges):  # 按输入顺序枚举边，下标 i 就是题目要求的边编号
            g[a].append((b, i))  # a 一侧记录 (邻居 b, 边下标 i)
            g[b].append((a, i))  # b 一侧记录 (邻居 a, 边下标 i)

        ans = []  # 收集需要翻转的边下标

        def dfs(a: int, fa: int) -> bool:  # dfs(a, fa)：返回以 a 为根的子树是否还需向上翻转
            rev = start[a] != target[a]  # 先只看节点 a 自身的 start 与 target 是否不同
            for b, i in g[a]:  # 遍历 a 的所有邻边
                if b != fa and dfs(b, a):  # 跳过父边；子树返回真说明必须翻转 a-b 这条边
                    ans.append(i)  # 记录被翻转的边下标
                    rev = not rev  # 翻边会连带翻转 a 自身，所以自己的标记取反
            return rev  # 把 a 的最终标记交回给父节点

        if dfs(0, -1):  # 根节点若仍有残留标记，说明差异无法消除
            return [-1]  # 按题意返回 [-1]
        ans.sort()  # 按题目要求把边下标升序排列
        return ans  # 返回结果
