# 题目：1916. 统计为蚁群构筑房间的不同顺序（Count Ways to Build Rooms in an Ant Colony）
# 思路：前驱关系构成以 0 为根的树，递归后序遍历；合并兄弟子树时把 cn 个节点插入已合并的 nodes_in_tree 个节点序列，乘组合数 C(nodes_in_tree+cn, cn)。
# 时间复杂度：O(n)，每个节点只递归一次；空间复杂度：O(n)，存两套邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def waysToBuildRooms(self, prevRoom: List[int]) -> int:  # prevRoom[i] 是房间 i 的前驱房间（房间 0 无前驱），返回合法的建造顺序数
        modulo = 10**9 + 7  # 答案取模的大质数
        ingoing = defaultdict(set)  # 记录每个房间的前驱集合，用来还原依赖关系
        outgoing = defaultdict(set)  # 记录每个房间的子房间集合，构成以 0 为根的树

        for i in range(1, len(prevRoom)):  # 房间 0 是根，从 1 号开始为每个房间建边
            ingoing[i].add(prevRoom[i])  # i 的前驱是 prevRoom[i]
            outgoing[prevRoom[i]].add(i)  # 反向记录：prevRoom[i] 多了一个子房间 i
        ans = [1]  # 用单元素列表充当可变累加器，因为闭包内无法重新绑定外层的局部变量

        def recurse(i):  # 返回以 i 为根的子树的节点数，并把子树内部的顺序方案数乘进 ans
            if len(outgoing[i]) == 0:  # 叶子房间没有子节点，直接作为递归出口
                return 1  # 单个节点本身只有一种（自身）

            nodes_in_tree = 0  # 已经合并过的兄弟子树节点总数
            for v in outgoing[i]:  # 依次递归处理每个子房间
                cn = recurse(v)  # 子树的节点数（其内部顺序方案已在递归过程中计入 ans）
                if nodes_in_tree != 0:  # 第一棵子树不需要交错；已有节点时才需要乘组合数
                    ans[0] *= comb(nodes_in_tree + cn, cn)  # 把 cn 个节点插入 nodes_in_tree 个已有节点的序列，方案数 C(nodes_in_tree+cn, cn)
                    ans[0] %= modulo  # 立即取模，避免大整数不断膨胀
                nodes_in_tree += cn  # 更新已合并的节点总数
            return nodes_in_tree + 1  # 加上 i 自己，返回整棵子树的节点数

        recurse(0)  # 从根房间开始递归，触发整棵树的方案数统计
        return ans[0] % modulo  # 返回总方案数，最后再取一次模保底
