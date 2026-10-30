# 题目：1697. 检查边长度限制的路径是否存在（Checking Existence of Edge Length Limited Paths）
# 思路：离线处理。边按长度升序、询问按 limit 升序，用并查集逐步把长度小于当前 limit 的边并入，再判断两端点是否连通。
# 时间复杂度：O((E + Q) log (E + Q))，排序为主，并查集近似常数；空间复杂度：O(n + Q)，存并查集父指针与答案。
class Solution:  # LeetCode 约定的题解类
    def distanceLimitedPathsExist(
        self, n: int, edgeList: List[List[int]], queries: List[List[int]]
    ) -> List[bool]:  # n：点数；edgeList：无向边 [u, v, w]；queries：询问 [a, b, limit]
        def find(x):  # 路径压缩的查找函数，返回 x 所属集合的代表元
            if p[x] != x:  # 不是根就继续向上找
                p[x] = find(p[x])  # 递归找到根，并把路径上的点直接挂到根上
            return p[x]  # 返回根，即所属集合的代表元

        p = list(range(n))  # 并查集父指针，初始时每个点各自成集合
        edgeList.sort(key=lambda x: x[2])  # 边按长度升序，便于随 limit 增大逐条加入
        j = 0  # 下一条待加入的边在 edgeList 中的下标
        ans = [False] * len(queries)  # 按原始询问下标保存答案
        for i, (a, b, limit) in sorted(enumerate(queries), key=lambda x: x[1][2]):  # 询问按 limit 升序，同时保留原下标 i
            while j < len(edgeList) and edgeList[j][2] < limit:  # 把所有长度严格小于 limit 的边并入并查集
                u, v, _ = edgeList[j]  # 取出该边的两个端点，权值已不需要
                p[find(u)] = find(v)  # 合并两个端点所在的集合
                j += 1  # 该边处理完毕，指向下一条
            ans[i] = find(a) == find(b)  # 根相同说明存在一条所有边都小于 limit 的路径
        return ans  # 返回按原始顺序排列的答案
