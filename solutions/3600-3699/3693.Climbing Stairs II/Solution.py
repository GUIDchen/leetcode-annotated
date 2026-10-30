# 3693. Climbing Stairs II（3693. 爬楼梯 II）
# 核心思路：用 f[i] 表示到达第 i 级台阶的最小花费；因为每次最多跳 3 级，所以 f[i] = min(f[i-j] + costs[i-1] + j²)，j = 1..3，跳跃距离的平方作为额外代价。
# 复杂度：时间 O(3n) 即 O(n)，空间 O(n)。
class Solution:  # 定义题解类
    def climbStairs(self, n: int, costs: List[int]) -> int:  # 主函数：返回到达第 n 级台阶的最小花费
        n = len(costs)  # 台阶数按 costs 数组长度为准（覆盖入参 n）
        f = [inf] * (n + 1)  # f[i] 表示到达第 i 级的最小花费，初始为无穷大
        f[0] = 0  # 地面（第 0 级）花费为 0
        for i, x in enumerate(costs, 1):  # 逐级递推，enumerate 的起始下标取 1
            for j in range(i - 3, i):  # 枚举上一次所在的台阶 j，最多往前跳 3 级
                if j >= 0:  # 跳过越界的位置
                    f[i] = min(f[i], f[j] + x + (i - j) ** 2)  # 转移：上一级花费 + 本级花费 + 跳跃距离的平方
        return f[n]  # 返回到达第 n 级的最小花费
