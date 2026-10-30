# 题目：1782. 统计点对的数目（Count Pairs Of Nodes）
# 思路：先排序度数，用二分统计所有「度数之和 > 阈值的点对」，再枚举有边的点对做去重修正（减掉重边条数后不达标的多算了一次）。
# 时间复杂度：O(E + n log n + q * (n log n + E))，q 为查询数；空间复杂度：O(n + E)，存度数、点对表与答案。
class Solution:  # LeetCode 约定的题解类
    def countPairs(  # 入口方法：统计满足条件的点对数目
        self, n: int, edges: List[List[int]], queries: List[int]  # self 是实例本身，n 是点数，edges 是无向边表，queries 是若干阈值
    ) -> List[int]:  # 返回列表：每个查询对应一个答案
        cnt = [0] * n  # cnt[i] 是点 i 的度数（参与的无向边条数，重边按条累加）
        g = defaultdict(int)  # 键是（小, 大）点对，值是这两点之间的重边条数
        for a, b in edges:  # 逐条边建立度数表与重边表
            a, b = a - 1, b - 1  # 题目是 1 基下标，转成 0 基
            a, b = min(a, b), max(a, b)  # 规范成小下标在前，保证同一个点对映射到同一个键
            cnt[a] += 1  # a 的度数加一
            cnt[b] += 1  # b 的度数加一
            g[(a, b)] += 1  # 这对点之间的重边计数加一

        s = sorted(cnt)  # 排序后的度数数组，便于对「度数之和 > t」做二分统计
        ans = [0] * len(queries)  # 每个查询对应一个答案
        for i, t in enumerate(queries):  # 逐个查询处理，t 是当前阈值
            for j, x in enumerate(s):  # 枚举点对中较小的那个点的下标 j
                k = bisect_right(s, t - x, lo=j + 1)  # 在 j 之后找第一个度数 > t - x 的位置
                ans[i] += n - k  # 这些点的度数 x + s[k'] 都大于 t，计入答案
            for (a, b), v in g.items():  # 修正：上面用的是度数之和，相连的两点会把公共边算两遍
                if cnt[a] + cnt[b] > t and cnt[a] + cnt[b] - v <= t:  # 度和达标，但扣掉重边条数后不达标
                    ans[i] -= 1  # 说明这对点在二分统计里被多算了一次，扣掉
        return ans  # 返回每个查询的答案
