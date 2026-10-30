# 题目：1719. 重构一棵树的方案数（Number Of Ways To Reconstruct A Tree）难度：困难
# 思路：pairs 给出树上的“祖先关系”边。先建邻接表并按度数（祖先个数）升序自底向上扫描，每个点 x 后面第一个与它相邻的点 y 就是它的父亲；若 x 的某个邻居 z 不是 y 的邻居，说明祖先关系自相矛盾返回 0；若某对父子度数相同则方案数至少为 2；找不到父亲的点（根）多于 1 个也返回 0。
# 时间复杂度：O(m^2)，m = 510 为编号上界；空间复杂度：O(m^2)，邻接布尔矩阵。
class Solution:  # LeetCode 约定的题解类
    def checkWays(self, pairs: List[List[int]]) -> int:  # pairs：祖先关系边集，返回方案数 0/1/2
        g = [[False] * 510 for _ in range(510)]  # 邻接布尔矩阵：g[a][b] 表示 a 与 b 之间有祖先关系边
        v = defaultdict(list)  # v[a]：a 的所有祖先（图中与 a 相邻的点）
        for x, y in pairs:  # 逐条边建图
            g[x][y] = g[y][x] = True  # 双向标记邻接关系
            v[x].append(y)  # x 的祖先列表加入 y
            v[y].append(x)  # y 的祖先列表加入 x
        nodes = []  # 收集所有出现过的点
        for i in range(510):  # 编号范围 0..509，覆盖题目所有编号
            if v[i]:  # 只处理出现在 pairs 里的点
                nodes.append(i)  # 记录该点
                g[i][i] = True  # 自己也算自己的祖先，方便后面做“包含”判断
        nodes.sort(key=lambda x: len(v[x]))  # 按度数升序：祖先少的点在树中层级更低，先处理
        equal = False  # 是否存在一对度数相同的父子（此时至少有两棵树都合法）
        root = 0  # 找不到父亲的点数，即候选根的数量
        for i, x in enumerate(nodes):  # 自底向上为每个点确定父亲
            j = i + 1  # 从度数比它大的点开始找父亲
            while j < len(nodes) and not g[x][nodes[j]]:  # 跳过所有不与 x 相邻的点
                j += 1  # 继续往后找
            if j < len(nodes):  # 找到了父亲候选 y
                y = nodes[j]  # y 就是 x 的父亲
                if len(v[x]) == len(v[y]):  # 父子度数相同
                    equal = True  # 两者可互换，方案不止一种
                for z in v[x]:  # 遍历 x 的每个祖先 z
                    if not g[y][z]:  # z 也必须是 y 的祖先，否则祖先关系矛盾
                        return 0  # 无法构树
            else:  # 后面没有相邻点，说明 x 是候选根
                root += 1  # 根的数量加一
        if root > 1:  # 根多于一个：图不连通
            return 0  # 无法构成一棵树
        return 2 if equal else 1  # 有两解返回 2，否则唯一解返回 1
