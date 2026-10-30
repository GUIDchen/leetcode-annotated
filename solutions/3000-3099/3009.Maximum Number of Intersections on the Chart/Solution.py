# 题目：3009. 折线图上的最大交点数量（Maximum Number of Intersections on the Chart）
# 核心思路：把每条线段覆盖的 y 坐标区间映射到 2 倍坐标上（消去半单位），用差分字典记录区间增减，再按坐标排序扫描取最大重叠层数。
# 时间复杂度：O(n log n)，排序差分键；空间复杂度：O(n)，差分字典最多 2n 个键。
class Solution:  # LeetCode 约定的题解类
    def maxIntersectionCount(self, y: List[int]) -> int:  # y 是折线在各整数 x 处的 y 坐标
        n = len(y)  # 折线的点数
        line = defaultdict(int)  # 差分字典：key 是坐标，value 是该坐标处覆盖层数的增量
        for i in range(1, n):  # 逐段考察折线的每条边（共 n-1 段）
            start = 2 * y[i - 1]  # 起点坐标乘 2，避免后半段的中点出现小数
            end = 2 * y[i] + (0 if i == n - 1 else (-1 if y[i] > y[i - 1] else 1))  # 终点坐标：最后一段不再外延，其余段按上升/下降偏半个单位（乘 2 后即 ±1）
            line[min(start, end)] += 1  # 差分：区间左端点覆盖层数加一
            line[max(start, end) + 1] -= 1  # 差分：区间右端点之后覆盖层数减一
        ans = intersection = 0  # ans 记录最大交点个数，intersection 是当前重叠线段数
        for _, count in sorted(line.items()):  # 按坐标从小到大扫描差分字典
            intersection += count  # 累加差分增量，得到当前坐标处覆盖的线段数
            ans = max(ans, intersection)  # 用当前覆盖数更新最大值
        return ans  # 返回折线图上的最大交点数量
