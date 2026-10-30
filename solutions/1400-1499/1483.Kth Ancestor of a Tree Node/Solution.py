# 题目：1483. 树节点的第 K 个祖先（Kth Ancestor of a Tree Node）
# 核心思路：倍增预处理 p[i][j] = 节点 i 向上 2^j 步的祖先；查询时把 k 的二进制位从高到低逐位跳跃。
# 时间复杂度：预处理 O(n log n)，单次查询 O(log n)；空间复杂度：O(n log n)。
class TreeAncestor:  # 题解类：初始化时建表，之后支持 O(log k) 查询
    def __init__(self, n: int, parent: List[int]):  # n 为节点数，parent[i] 为 i 的父亲（根为 -1）
        self.p = [[-1] * 18 for _ in range(n)]  # 倍增表：p[i][j] 表示节点 i 向上 2^j 步的祖先，-1 表示不存在
        for i, fa in enumerate(parent):  # 遍历每个节点及其父亲
            self.p[i][0] = fa  # j = 0 即向上一步，就是直接父亲
        for j in range(1, 18):  # 由 2^(j-1) 递推 2^j
            for i in range(n):  # 对每个节点求第 2^j 个祖先
                if self.p[i][j - 1] == -1:  # 中间祖先不存在
                    continue  # 该项保持 -1 并跳过
                self.p[i][j] = self.p[self.p[i][j - 1]][j - 1]  # 两段 2^(j-1) 步拼接成 2^j 步
        # 查询时把 k 按二进制拆位，从高位到低位跳跃
    def getKthAncestor(self, node: int, k: int) -> int:  # 返回 node 的第 k 个祖先，不存在返回 -1
        for i in range(17, -1, -1):  # 从最高位 17 枚举到 0
            if k >> i & 1:  # k 的第 i 位为 1，需要跳 2^i 步
                node = self.p[node][i]  # 向上跳 2^i 步
                if node == -1:  # 已越过根，第 k 个祖先不存在
                    break  # 提前结束跳跃
        return node  # 返回祖先编号，-1 表示不存在


# Your TreeAncestor object will be instantiated and called as such:
# obj = TreeAncestor(n, parent)
# param_1 = obj.getKthAncestor(node,k)
