# 题目：2479. 两个不重叠子树的最大异或值（Maximum XOR of Two Non-Overlapping Subtrees）
# 思路：第一次后序 DFS 求出每棵子树的和 s[i]；第二次后序 DFS 在「离开节点」时才把 s[i] 插入 01-Trie，插入前先查询 Trie 中已有值（即与当前子树不重叠的其它子树）能得到的最大异或，从而保证两棵子树互不重叠。
# 时间复杂度：O(n·logC)，每个节点在 48 位 Trie 上走一趟；空间复杂度：O(n·logC)，Trie 节点总数。
class Trie:  # 01-Trie：按二进制位从高到低保存子树和，用来求最大异或
    def __init__(self):  # 构造函数
        self.children = [None] * 2  # 两个孩子：下标 0 表示这一位取 0，下标 1 表示取 1

    def insert(self, x):  # 把整数 x 的 48 个二进制位插入 Trie
        node = self  # 从根节点开始
        for i in range(47, -1, -1):  # 从第 47 位（最高位）枚举到第 0 位
            v = (x >> i) & 1  # 取出 x 的第 i 位（0 或 1）
            if node.children[v] is None:  # 该分支不存在就新建节点
                node.children[v] = Trie()  # 创建子 Trie 并挂在对应位的指针上
            node = node.children[v]  # 向下走一层

    def search(self, x):  # 在 Trie 中查一个数与 x 异或能得到的最大值
        node = self  # 从根开始匹配
        res = 0  # 累积的异或结果
        for i in range(47, -1, -1):  # 逐位贪心，从高位到低位
            v = (x >> i) & 1  # x 的第 i 位
            if node is None:  # 防御性判断：节点为空说明没有可匹配的数
                return res  # 返回已经积累的结果
            if node.children[v ^ 1]:  # 若存在与当前位相反的分支，这一位异或可得 1，优先走它
                res = res << 1 | 1  # 结果左移一位并把最低位置 1
                node = node.children[v ^ 1]  # 走到相反位分支
            else:  # 没有相反位分支，只能将就相同位
                res <<= 1  # 结果左移一位，最低位补 0
                node = node.children[v]  # 走到相同位分支
        return res  # 返回最大异或值


class Solution:  # LeetCode 约定的题解类
    def maxXor(self, n: int, edges: List[List[int]], values: List[int]) -> int:  # n：节点数；edges：无向边；values：点权；返回两棵不重叠子树和的最大异或值
        def dfs1(i, fa):  # 第一次 DFS（后序）：求以 i 为根的子树点权和，fa 是父节点（-1 表示根）
            t = values[i]  # 先把自己这一份点权放进累加器
            for j in g[i]:  # 遍历所有邻居
                if j != fa:  # 跳过父节点，避免走回上层
                    t += dfs1(j, i)  # 递归累加孩子的子树和
            s[i] = t  # 记下当前节点的子树和
            return t  # 返回给父节点继续累加

        def dfs2(i, fa):  # 第二次 DFS（后序）：离开节点时才插入 Trie，保证两棵子树不重叠
            nonlocal ans  # 声明 ans 来自外层函数，才能在闭包内赋值
            ans = max(ans, tree.search(s[i]))  # 先用 Trie 中已有的（不重叠的）子树和查询最大异或
            for j in g[i]:  # 遍历邻居
                if j != fa:  # 跳过父节点
                    dfs2(j, i)  # 递归处理孩子，孩子会先入 Trie
            tree.insert(s[i])  # 后序插入自己，避免与自己的子树重叠

        g = defaultdict(list)  # 邻接表建图（defaultdict 访问不存在的键会自动创建空列表）
        for a, b in edges:  # 遍历每条无向边
            g[a].append(b)  # a 的邻居加上 b
            g[b].append(a)  # b 的邻居加上 a（无向边存两次）
        s = [0] * n  # s[i] 保存以 i 为根的子树点权和
        dfs1(0, -1)  # 以 0 为根启动第一次 DFS，填好 s
        ans = 0  # 答案初值 0
        tree = Trie()  # 空的 01-Trie
        dfs2(0, -1)  # 启动第二次 DFS，边查询边插入
        return ans  # 返回最大异或值
