# 题目：3143. 正方形中的最多点数（Maximum Points Inside the Square）
# 思路：以原点为中心、半边长 k 的正方形覆盖 max(|x|,|y|) ≤ k 的点；按这个距离从小到大分层，层内标签只要不与内层重复就能整层纳入，出现重复即停止扩大。
# 时间复杂度：O(n log n)，需要对距离排序；空间复杂度：O(n)，保存分层结果与已占用标签集合。
class Solution:  # LeetCode 约定的题解类
    def maxPointsInsideSquare(self, points: List[List[int]], s: str) -> int:  # points：所有点坐标；s：每个点对应的标签字符
        g = defaultdict(list)  # g：切比雪夫距离 → 该距离上的点下标列表
        for i, (x, y) in enumerate(points):  # 同时取得下标 i 和坐标 (x, y)
            g[max(abs(x), abs(y))].append(i)  # 按 max(|x|,|y|) 把下标分到对应距离的桶里
        vis = set()  # vis：记录已被更内层占用的标签字符
        ans = 0  # ans：已经确认可以整层纳入的点数
        for d in sorted(g):  # 按距离从小到大遍历，等价于正方形逐步扩大
            idx = g[d]  # 取出本层的所有点下标
            for i in idx:  # 逐个检查本层的点
                if s[i] in vis:  # 标签已在更内层出现过，正方形不能再扩大
                    return ans  # 直接返回此前累计的点数
                vis.add(s[i])  # 标签没冲突，标记为已占用
            ans += len(idx)  # 本层全部合法，整层计入答案（len(idx) 即本层点数）
        return ans  # 所有层都不冲突，返回全部点数
