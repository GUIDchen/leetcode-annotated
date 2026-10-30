# 题目：1135. 最低成本连通所有城市（Connecting Cities With Minimum Cost）
# 思路：Kruskal 最小生成树：边按成本排序，用并查集判断加边是否成环，只累加不成环的边。
# 时间复杂度：O(m log m) 排序 + O(m α(n)) 并查集；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, n: int, connections: List[List[int]]) -> int:  # n 是城市个数，connections 每项是 [城市1, 城市2, 成本]（编号从 1 开始），返回最小连通成本或 -1
        def find(x):  # 并查集查找，返回 x 所在连通块的根；这里用闭包，p 稍后才定义，靠延迟绑定在调用时才解析
            if p[x] != x:  # 父节点不是自己，说明 x 不是根
                p[x] = find(p[x])  # 路径压缩：递归找到根后把 x 直接挂到根下
            return p[x]  # 返回根节点

        connections.sort(key=lambda x: x[2])  # Kruskal 第一步：按成本升序排序，保证贪心先选便宜边
        p = list(range(n))  # 并查集父节点数组，初始每个城市自成一类
        ans = 0  # 已选边的累计成本
        for x, y, cost in connections:  # 按成本从小到大逐条考察边
            x, y = x - 1, y - 1  # 题目编号 1..n 转成 0..n-1 的下标
            if find(x) == find(y):  # 两端点已连通，再加这条边就成环，直接丢弃
                continue  # 跳过这条边
            p[find(x)] = find(y)  # 合并两个连通块：把 x 的根挂到 y 的根下
            ans += cost  # 这条边入选生成树，累加成本
            n -= 1  # 成功合并一次，连通块数量减 1（复用参数 n 计数）
            if n == 1:  # 只剩一个连通块，说明生成树已完成
                return ans  # 提前返回最小成本
        return -1  # 所有边试完仍然不连通，返回 -1
