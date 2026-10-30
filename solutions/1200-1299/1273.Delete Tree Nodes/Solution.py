class Solution:  # LeetCode 约定的题解类
    def deleteTreeNodes(self, nodes: int, parent: List[int], value: List[int]) -> int:  # nodes：节点总数；parent：每个节点的父节点；value：每个节点的值
        def dfs(i):  # dfs(i)：返回以 i 为根的 (子树值之和, 保留下来的节点个数)
            s, m = value[i], 1  # s 是子树值之和（初值当前节点值），m 是节点个数（初值 1）
            for j in g[i]:  # 遍历当前节点的所有孩子
                t, n = dfs(j)  # 递归求出孩子子树的「值之和」与「节点个数」
                s += t  # 累加孩子的值之和
                m += n  # 累加孩子的节点个数
            if s == 0:  # 子树值之和为 0，整棵子树都要删除
                m = 0  # 节点数记 0，表示这棵子树不再保留
            return (s, m)  # 返回本子树的 (值之和, 节点个数)

        g = defaultdict(list)  # 邻接表；dfs 里用到的 g 在这里建好，调用时已存在
        for i in range(1, nodes):  # 0 号是根，从 1 号开始把节点挂到父节点下
            g[parent[i]].append(i)  # 把节点 i 接到父节点 parent[i] 的孩子列表里
        return dfs(0)[1]  # 根子树剩下的节点个数就是答案
