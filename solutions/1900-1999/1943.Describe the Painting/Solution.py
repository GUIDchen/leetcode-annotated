# 题目：1943. 描述绘画结果（Describe the Painting）
# 思路：差分数组 + 排序：每段在 l 处加 c、在 r 处减 c，再把坐标排序做前缀和，相邻坐标构成区间，颜色和不为 0 的区间即为答案。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，差分表与排序后的坐标列表。
class Solution:  # LeetCode 约定的题解类
    def splitPainting(self, segments: List[List[int]]) -> List[List[int]]:  # segments：每段画的 (起点, 终点, 颜色值)
        d = defaultdict(int)  # 差分表：坐标 → 该坐标处的颜色变化量；defaultdict(int) 让未出现的键自动为 0
        for l, r, c in segments:  # 遍历每一段画线
            d[l] += c  # 左端点处颜色增加 c（同一坐标自然累加）
            d[r] -= c  # 右端点处颜色减少 c，表示这段画到此结束
        s = sorted([[k, v] for k, v in d.items()])  # 把差分表整理成按坐标升序的 [坐标, 差分值] 列表
        n = len(s)  # n 是不同坐标的个数
        for i in range(1, n):  # 对差分值做前缀和，得到每个坐标起始处的颜色和
            s[i][1] += s[i - 1][1]  # s[i][1] 累加上前一个坐标的差分值
        return [[s[i][0], s[i + 1][0], s[i][1]] for i in range(n - 1) if s[i][1]]  # 相邻坐标构成区间 [s[i][0], s[i+1][0])，颜色和不为 0 才输出
