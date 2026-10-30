# 题目：2508. 添加边使所有节点度数都为偶数（Add Edges to Make Degrees of All Nodes Even）
# 思路：统计度数为奇数的节点集合，最多加两条边；0 个直接成立，2 个可一条边直连或经中转点连两条，4 个则检查三种两两配对的边是否都不存在。
# 时间复杂度：O(n + m)，n 为节点数、m 为边数；空间复杂度：O(n + m)，存储邻接表。
class Solution:  # LeetCode 约定的题解类
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:  # n 是节点数，edges 是已有的无向边
        g = defaultdict(set)  # 邻接表：字典的值是集合，便于 O(1) 判断两个节点之间是否已有边
        for a, b in edges:  # 逐条读入已有的边
            g[a].add(b)  # 把 b 登记为 a 的邻居
            g[b].add(a)  # 无向边需要双向登记
        vs = [i for i, v in g.items() if len(v) & 1]  # 收集所有度数为奇数的节点（只遍历出现过的节点）
        if len(vs) == 0:  # 没有奇度节点，一条边都不用加
            return True  # 已经满足所有节点度数为偶数
        if len(vs) == 2:  # 恰好两个奇度节点：可以一条边直连，或用两条边经中转点
            a, b = vs  # 取出这两个奇度节点
            if a not in g[b]:  # a、b 之间原本没有边
                return True  # 直接连一条边就能修正
            return any(a not in g[c] and c not in g[b] for c in range(1, n + 1))  # 枚举中转点 c，两条新边都不存在即可
        if len(vs) == 4:  # 四个奇度节点：两条新边必须两两配对，共三种配对方式
            a, b, c, d = vs  # 取出四个奇度节点
            if a not in g[b] and c not in g[d]:  # 配对 (a,b) 与 (c,d)，且两条边都还不存在
                return True  # 该配对方案可行
            if a not in g[c] and b not in g[d]:  # 配对 (a,c) 与 (b,d)
                return True  # 该配对方案可行
            if a not in g[d] and b not in g[c]:  # 配对 (a,d) 与 (b,c)
                return True  # 该配对方案可行
            return False  # 三种配对都被已有边占用，无法完成
        return False  # 奇度节点数不是 0/2/4，两条边无法全部消掉，返回不可能
