# 题目：2977. 转换字符串的最小成本 II（Minimum Cost to Convert String II）
# 思路：规则串插入 Trie 并编号，Floyd 求编号间最小转换成本；再用 @cache 记忆化的 dfs 从 i 出发，让 source、target 同步沿两条 Trie 下行，两边都落在规则串结尾时尝试整段转换。
# 时间复杂度：O(V^3 + n^2)，V 为规则串编号数、n 为串长；空间复杂度：O(V^2 + n)，邻接矩阵与记忆化数组。
class Node:  # Trie 结点：26 个儿子指针 + 一个规则串编号
    __slots__ = ["children", "v"]  # __slots__ 固定属性名，省掉每个结点一个字典的开销

    def __init__(self):  # 构造函数
        self.children: List[Node | None] = [None] * 26  # 26 个小写字母分支，初始都为空
        self.v = -1  # v 为字符串编号，-1 表示这里不是一个规则串的结尾


class Solution:  # LeetCode 约定的题解类
    def minimumCost(  # minimumCost：求最小总成本
        self,  # self 为实例本身
        source: str,  # 原串
        target: str,  # 目标串
        original: List[str],  # 转换规则的起点串
        changed: List[str],  # 转换规则的终点串
        cost: List[int],  # 与规则一一对应的成本
    ) -> int:  # 参数列表结束，返回 int
        m = len(cost)  # 规则条数 m，编号上界为 2m
        g = [[inf] * (m << 1) for _ in range(m << 1)]  # 构造 (2m)x(2m) 矩阵，初值 inf 表示不可达
        for i in range(m << 1):  # 遍历所有编号，初始化对角线
            g[i][i] = 0  # 同一字符串转成自己不需要任何代价
        root = Node()  # Trie 根结点
        idx = 0  # 已分配的字符串编号个数

        def insert(w: str) -> int:  # 把字符串 w 插入 Trie，返回其编号
            node = root  # 从根开始走
            for c in w:  # 逐字符下行，深度即串长
                i = ord(c) - ord("a")  # 字符映射成 0..25
                if node.children[i] is None:  # 该分支还不存在
                    node.children[i] = Node()  # 新建结点挂到该分支
                node = node.children[i]  # 沿分支走到下一层
            if node.v < 0:  # 这个串还没有分配过编号
                nonlocal idx  # 声明要修改外层函数的 idx（闭包内赋值必须用 nonlocal）
                node.v = idx  # 分配新编号
                idx += 1  # 编号计数自增
            return node.v  # 返回该串的编号

        @cache  # @cache 让 dfs 自动记忆化，等价于手写的记忆化数组
        def dfs(i: int) -> int:  # 从下标 i 转换到串尾的最小成本
            if i >= len(source):  # 已经扫完整个串
                return 0  # 收尾成本为 0
            res = dfs(i + 1) if source[i] == target[i] else inf  # 字符相同就能免费跳过一位；不同则先记为不可达
            p = q = root  # p、q 分别沿 source、target 的 Trie 路径下行
            for j in range(i, len(source)):  # 枚举起止区间 [i, j] 作为一段整体转换
                p = p.children[ord(source[j]) - ord("a")]  # 同步下行 source 的第 j 个字符
                q = q.children[ord(target[j]) - ord("a")]  # 同步下行 target 的第 j 个字符
                if p is None or q is None:  # 任一边走不下去，更长的段也不可能匹配
                    break  # 提前结束枚举
                if p.v < 0 or q.v < 0:  # 两边都必须落在某个规则串的结尾才有编号
                    continue  # 这段不能整段转换，试更长的段
                res = min(res, dfs(j + 1) + g[p.v][q.v])  # 整段转换成本 + 剩余部分的最优成本，取较小值
            return res  # 返回本位置的最小成本（由 @cache 缓存）

        for x, y, z in zip(original, changed, cost):  # 逐条规则编号并写入矩阵
            x = insert(x)  # 起点串的编号
            y = insert(y)  # 终点串的编号
            g[x][y] = min(g[x][y], z)  # 保留最便宜的一条规则
        for k in range(idx):  # Floyd 的中间点 k
            for i in range(idx):  # 起点 i
                if g[i][k] >= inf:  # i→k 不可达就无需松弛
                    continue  # 跳过整个内层循环
                for j in range(idx):  # 终点 j
                    # 下面这行是被注释掉的原始写法（直接用 min 赋值），与下一行的 if 判断等价
                    # g[i][j] = min(g[i][j], g[i][k] + g[k][j])
                    if g[i][k] + g[k][j] < g[i][j]:  # 松弛：i→k→j 更便宜则更新
                        g[i][j] = g[i][k] + g[k][j]  # 直接赋值：i→k→j 更便宜就更新（与上面注释掉的写法等价）

        ans = dfs(0)  # 从下标 0 开始求最优成本
        return -1 if ans >= inf else ans  # 无解返回 -1，否则返回最小总成本
