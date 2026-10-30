# 3623. Count Number of Trapezoids I（3623. 统计梯形的数目 I）
# 核心思路：按 y 坐标分组，同一水平线上任取两点得到一条水平底边；不同水平线各取一条底边即构成梯形，用前缀和边遍历边累加组合数。
# 复杂度：时间 O(n)（哈希计数 + 一次遍历），空间 O(n)（按 y 的行数）。
class Solution:  # 定义题解类
    def countTrapezoids(self, points: List[List[int]]) -> int:  # 统计所有水平线组合出的梯形数目
        mod = 10**9 + 7  # 取模常量，防止结果溢出
        cnt = Counter(p[1] for p in points)  # 统计每条水平线（y 坐标）上的点数
        ans = s = 0  # ans 为答案，s 为之前所有行可选底边数之和
        for v in cnt.values():  # 遍历每一行的点数
            t = v * (v - 1) // 2  # 该行任取两点形成的底边数
            ans = (ans + s * t) % mod  # 与之前的行两两组合，累加新梯形
            s += t  # 把当前行计入前缀和，供后续行配对
        return ans  # 返回梯形总数
