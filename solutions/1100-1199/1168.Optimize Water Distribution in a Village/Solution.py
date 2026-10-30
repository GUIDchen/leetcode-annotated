# 题目：1168. 水资源分配优化（Optimize Water Distribution in a Village）
# 思路：虚拟出一个编号 0 的水源点，「在房子 i 打井」等价于边 (0, i) 代价为 wells[i]；把所有边排序后跑 Kruskal 最小生成树。
# 时间复杂度：O(E log E)，E = n + len(pipes)；空间复杂度：O(n + E)，并查集与边表都是线性规模。
class Solution:  # 题解类
    def minCostToSupplyWater(  # 求让每个房子都通水的最小总费用
        self, n: int, wells: List[int], pipes: List[List[int]]  # n 个房子；wells 是在房子处打井的费用；pipes 是房子之间铺管道的费用
    ) -> int:  # 多行参数列表在此收尾
        def find(x: int) -> int:  # 递归查找并查集的根节点
            if p[x] != x:  # 父亲不是自己说明它还不是根
                p[x] = find(p[x])  # 路径压缩：把 x 直接挂到根上，后续查找更快
            return p[x]  # 返回所在连通块的根

        for i, w in enumerate(wells, 1):  # 把「在 i 号房子打井」抽象成虚拟源点 0 到 i 的一条边
            pipes.append([0, i, w])  # 边的代价就是打井费用
        pipes.sort(key=lambda x: x[2])  # 按边权升序排序，为 Kruskal 最小生成树做准备
        p = list(range(n + 1))  # 并查集初始化，每个节点各自成一个集合
        ans = 0  # 累计最小费用
        for a, b, c in pipes:  # 按代价从小到大遍历所有边
            pa, pb = find(a), find(b)  # 取这条边两个端点所在连通块的根
            if pa != pb:  # 只有不在同一连通块时才合并，避免成环
                p[pa] = pb  # 合并两个连通块
                n -= 1  # 还需要合并的次数减一
                ans += c  # 采用这条边，把代价累加到答案
                if n == 0:  # 减到 0 说明生成树已完成
                    return ans  # 提前返回最小总费用
