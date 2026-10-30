# 3590. 第 K 小的路径异或和（Kth Smallest Path XOR Sum）
# 核心思路：先求根到每个节点的路径异或，再自底向上用按位 Trie 按“小并大”合并每个子树的异或集合；查询 (u,k) 即在该集合中取第 k 小的值。
# 复杂度：时间 O((n log n + q) · B)，空间 O(n · B)，其中 B = 17 为值域位数。
class BinarySumTrie:  # 按位 Trie，维护一个可去重的异或值集合，支持第 k 小查询
    def __init__(self):  # 构造函数
        self.count = 0  # 当前子树中包含的不同数值个数
        self.children = [None, None]  # 0/1 两个子节点，初始为空

    def add(self, num: int, delta: int, bit=17):  # 把 num 从第 bit 位开始插入（delta=1）或删除（delta=-1）
        self.count += delta  # 沿途节点的计数同步增减
        if bit < 0:  # 所有位都处理完了
            return  # 到达叶节点，递归出口
        b = (num >> bit) & 1  # 取出 num 的第 bit 位
        if not self.children[b]:  # 该分支的子节点还不存在
            self.children[b] = BinarySumTrie()  # 新建子节点
        self.children[b].add(num, delta, bit - 1)  # 递归处理下一位

    def collect(self, prefix=0, bit=17, output=None):  # 收集本 Trie 内的全部数值，用于小并大合并
        if output is None:  # 调用方没有传入结果列表
            output = []  # 新建一个结果列表
        if self.count == 0:  # 子树为空
            return output  # 没有值可收集，直接返回
        if bit < 0:  # 到达叶节点
            output.append(prefix)  # prefix 已拼成完整数值，放入结果
            return output  # 返回收集结果
        if self.children[0]:  # 存在 0 分支
            self.children[0].collect(prefix, bit - 1, output)  # 沿 0 位继续向下收集
        if self.children[1]:  # 存在 1 分支
            self.children[1].collect(prefix | (1 << bit), bit - 1, output)  # 沿 1 位继续向下收集，并把第 bit 位置 1
        return output  # 返回收集到的全部数值

    def exists(self, num: int, bit=17):  # 查询数值 num 是否已在集合中
        if self.count == 0:  # 空 Trie
            return False  # 必然不存在
        if bit < 0:  # 所有位都匹配到底
            return True  # 数值存在
        b = (num >> bit) & 1  # 取出当前位
        return self.children[b].exists(num, bit - 1) if self.children[b] else False  # 子节点存在才继续匹配，否则不存在

    def find_kth(self, k: int, bit=17):  # 返回集合中第 k 小（k 从 1 起）的值
        if k > self.count:  # k 超出集合大小
            return -1  # 不存在，返回 -1
        if bit < 0:  # 已经到达叶节点
            return 0  # 低位不再有贡献
        left_count = self.children[0].count if self.children[0] else 0  # 0 分支中包含的数值个数
        if k <= left_count:  # 第 k 小落在 0 分支
            return self.children[0].find_kth(k, bit - 1)  # 递归进入 0 分支
        elif self.children[1]:  # 否则落在 1 分支且该分支存在
            return (1 << bit) + self.children[1].find_kth(k - left_count, bit - 1)  # 加上当前位的权值后递归进入 1 分支
        else:  # 两个分支都不可用
            return -1  # 兜底返回 -1


class Solution:  # 主解类
    def kthSmallest(  # 入口：返回每个查询的答案
        self, par: List[int], vals: List[int], queries: List[List[int]]  # 参数：父节点数组、节点值、查询列表
    ) -> List[int]:  # 返回每个查询的结果列表
        n = len(par)  # 节点个数
        tree = [[] for _ in range(n)]  # 邻接表：每个节点保存其子节点
        for i in range(1, n):  # 节点 0 是根，从 1 开始建边
            tree[par[i]].append(i)  # 父节点 par[i] 指向子节点 i

        path_xor = vals[:]  # 先把每个节点的值作为路径异或的初值
        narvetholi = path_xor  # 保留一个指向同一列表的别名，不影响后续逻辑

        def compute_xor(node, acc):  # 计算路径异或，acc 为父节点的路径异或
            path_xor[node] ^= acc  # 把父路径的异或累加到当前节点
            for child in tree[node]:  # 遍历所有子节点
                compute_xor(child, path_xor[node])  # 把当前节点的路径异或继续向下传递

        compute_xor(0, 0)  # 从根开始计算，根的父路径异或为 0

        node_queries = defaultdict(list)  # 按起点节点归组查询
        for idx, (u, k) in enumerate(queries):  # 枚举查询及其原始下标
            node_queries[u].append((k, idx))  # 保存 (k, 原始下标)

        trie_pool = {}  # 每个节点对应的子树 Trie
        result = [0] * len(queries)  # 答案数组，长度等于查询数

        def dfs(node):  # 后序 DFS：合并子树 Trie 并回答本节点上的查询
            trie_pool[node] = BinarySumTrie()  # 为本节点新建一棵 Trie
            trie_pool[node].add(path_xor[node], 1)  # 先把自己的路径异或放进集合
            for child in tree[node]:  # 遍历所有子节点
                dfs(child)  # 先递归处理子树，得到子树的 Trie
                if trie_pool[node].count < trie_pool[child].count:  # 小并大：让 node 始终持有规模更大的 Trie
                    trie_pool[node], trie_pool[child] = (  # 交换两棵 Trie 的引用
                        trie_pool[child],  # 把规模更大的子树 Trie 换给 node
                        trie_pool[node],  # 把原 node 的 Trie 换给 child
                    )  # 交换完成
                for val in trie_pool[child].collect():  # 收集子 Trie 中的全部数值并逐个合并
                    if not trie_pool[node].exists(val):  # 集合语义需要去重
                        trie_pool[node].add(val, 1)  # 插入尚未存在的数值
            for k, idx in node_queries[node]:  # 处理挂在当前节点上的所有查询
                if trie_pool[node].count < k:  # 不同值不足 k 个
                    result[idx] = -1  # 无解，记 -1
                else:  # 否则
                    result[idx] = trie_pool[node].find_kth(k)  # 取集合中第 k 小的路径异或

        dfs(0)  # 从根开始自底向上合并
        return result  # 返回全部查询的答案
