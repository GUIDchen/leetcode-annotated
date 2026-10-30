# 题目：1519. 子树中标签相同的节点数（Number of Nodes in the Sub-Tree With the Same Label）
# 核心思路：DFS 后序统计；全局计数器 cnt 记录进入子树前、退出时两次的标签数量，差值就是该子树中同标签节点数。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，邻接表 + 递归栈。
class Solution:  # LeetCode 约定的题解类
    def countSubTrees(self, n: int, edges: List[List[int]], labels: str) -> List[int]:  # n：节点个数（本写法未用到）；edges：无向边；labels：每个节点的字符标签
        def dfs(i, fa):  # 内部递归函数：i 当前节点，fa 父节点（防止回走）
            ans[i] -= cnt[labels[i]]  # 进入子树前先减去已有的同类计数，记下快照
            cnt[labels[i]] += 1  # 把当前节点计入全局计数
            for j in g[i]:  # 遍历邻居
                if j != fa:  # 跳过父节点
                    dfs(j, i)  # 递归处理子节点
            ans[i] += cnt[labels[i]]  # 退出时加回同类计数，与快照的差值就是子树中同标签节点数

        g = defaultdict(list)  # 邻接表：defaultdict 会让没出现过的键自动得到空列表
        for a, b in edges:  # 逐条边建无向图
            g[a].append(b)  # a → b
            g[b].append(a)  # b → a
        cnt = Counter()  # 计数器，记录全局已访问的各标签出现次数
        ans = [0] * n  # 答案数组，长度 n，初始全 0
        dfs(0, -1)  # 从根 0 开始 DFS，父节点记为 -1
        return ans  # 返回答案
