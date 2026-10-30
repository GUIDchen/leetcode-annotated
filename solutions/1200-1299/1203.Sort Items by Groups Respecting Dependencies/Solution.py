# 题目：1203. 项目管理（Sort Items by Groups Respecting Dependencies）
# 思路：把约束拆成「组内项目依赖」与「组间依赖」两张图分别拓扑排序，先排出小组顺序，再按小组顺序对组内项目排序；任一张图成环即无解。
# 时间复杂度：O(n + m + E)，E 为 beforeItems 的总边数；空间复杂度：O(n + m + E)，需要存两张邻接表与度数数组。
class Solution:  # LeetCode 约定的题解类
    def sortItems(  # n：项目总数；m：组数
        self, n: int, m: int, group: List[int], beforeItems: List[List[int]]  # group：项目到组的映射（-1 表示未分组）；beforeItems：每个项目的前置依赖
    ) -> List[int]:  # 返回满足全部依赖的项目顺序，无解时返回空列表
        def topo_sort(degree, graph, items):  # 内部函数：只对 items 这批结点做拓扑排序，成环则返回空列表
            q = deque(i for _, i in enumerate(items) if degree[i] == 0)  # 双端队列初始装入 items 中所有入度为 0 的结点
            res = []  # 保存拓扑序结果
            while q:  # 队列非空说明还有可处理的结点
                i = q.popleft()  # 取队头作为当前要排的结点
                res.append(i)  # 前置约束已全部满足，直接放进答案
                for j in graph[i]:  # 遍历 i 的所有后继，解除它们对 i 的依赖
                    degree[j] -= 1  # 后继入度减一，表示又排掉了一个前置
                    if degree[j] == 0:  # 入度降为 0 说明后继的前置都排完了
                        q.append(j)  # 后继入队等待排序
            return res if len(res) == len(items) else []  # 排出的结点数等于这批结点数才无环，否则返回空列表

        idx = m  # 未分组项目要各自单独成组，新组号从 m 开始分配
        group_items = [[] for _ in range(n + m)]  # group_items[g] 存放组 g 的项目下标；最坏 n 个项目各成一組，故容量取 n + m
        for i, g in enumerate(group):  # 第一遍扫描：给未分组项目分配组号，并收集每个组包含的项目
            if g == -1:  # -1 表示该项目没有归属任何组
                group[i] = idx  # 给它单独开一个新组
                idx += 1  # 组号计数器递增，保证每个未分组项目组号不同
            group_items[group[i]].append(i)  # 把项目 i 记录到它所属组的列表中，供后续组内排序使用

        item_degree = [0] * n  # 项目级入度：还有多少个同组前置项目没排
        group_degree = [0] * (n + m)  # 组级入度：组 g 还有多少个前置组没排
        item_graph = [[] for _ in range(n)]  # 项目级邻接表：item_graph[j] 里的 i 表示 i 必须排在 j 之后
        group_graph = [[] for _ in range(n + m)]  # 组级邻接表：group_graph[gj] 里的 gi 表示组 gi 必须排在组 gj 之后
        for i, gi in enumerate(group):  # 第二遍扫描：遍历所有依赖关系，按同组 / 跨组分别建图
            for j in beforeItems[i]:  # j 是项目 i 的前置项目，即 j 必须排在 i 之前
                gj = group[j]  # 取得前置项目所属的组，用于判断是否同组
                if gi == gj:  # 两者同组：先后关系只能在组内解决，落到项目级图上
                    item_degree[i] += 1  # 项目 i 多了一个同组前置，入度加一
                    item_graph[j].append(i)  # 建立有向边 j -> i，表示 j 排在 i 前面
                else:  # 两者跨组：说明组 gj 必须整体排在组 gi 之前，落到组级图上
                    group_degree[gi] += 1  # 目标组 gi 的前置组数量加一
                    group_graph[gj].append(gi)  # 建立组级有向边 gj -> gi

        group_order = topo_sort(group_degree, group_graph, range(n + m))  # 第一步：对组级图做拓扑排序，候选是全部 n + m 个组
        if not group_order:  # 返回空列表说明组之间存在环，组间先后无法满足
            return []  # 题目无解，返回空列表
        ans = []  # 最终的项目排列结果
        for gi in group_order:  # 按组级拓扑序依次处理每一组
            items = group_items[gi]  # 取出本组要参与排序的项目下标集合
            item_order = topo_sort(item_degree, item_graph, items)  # 第二步：在本组内部按项目级依赖做拓扑排序
            if len(items) != len(item_order):  # 排出的项目数少于组内项目数，说明组内存在循环依赖
                return []  # 题目无解，返回空列表
            ans.extend(item_order)  # 把本组的组内顺序整体拼到答案末尾
        return ans  # 返回满足全部依赖的项目顺序
