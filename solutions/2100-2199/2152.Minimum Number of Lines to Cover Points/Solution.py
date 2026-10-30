# 题目：2152. 穿过所有点的所需最少直线数量（Minimum Number of Lines to Cover Points）
# 思路：状压 DP —— state 记录已被直线覆盖的点；每次取第一个未覆盖点 i，与另一个未覆盖点 j 确定直线并吞掉同线点，记忆化搜索最少直线数。
# 时间复杂度：O(2^n · n^3)，状态数乘以每次枚举的组合数；空间复杂度：O(2^n)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimumLines(self, points: List[List[int]]) -> int:  # points：所有点的坐标；返回覆盖全部点所需的最少直线数
        def check(i, j, k):  # 判断编号 i、j、k 的三个点是否共线
            x1, y1 = points[i]  # 第 i 个点的坐标
            x2, y2 = points[j]  # 第 j 个点的坐标
            x3, y3 = points[k]  # 第 k 个点的坐标
            return (x2 - x1) * (y3 - y1) == (x3 - x1) * (y2 - y1)  # 叉积为 0 即共线，用整数乘法避免浮点误差

        @cache  # 记忆化装饰器：同一个 state 只计算一次
        def dfs(state):  # state 的每一位标记对应点是否已被某条直线覆盖
            if state == (1 << n) - 1:  # 所有点都已覆盖
                return 0  # 不需要再加直线
            ans = inf  # 当前最优解初始化为无穷大
            for i in range(n):  # 找第一个尚未被覆盖的点 i
                if not (state >> i & 1):  # 第 i 位为 0，点 i 还没被覆盖
                    for j in range(i + 1, n):  # 再找未覆盖的点 j，与 i 一起确定一条直线
                        nxt = state | 1 << i | 1 << j  # 新状态：i、j 已覆盖
                        for k in range(j + 1, n):  # 检查后面的点 k 是否也落在这条直线上
                            if not (nxt >> k & 1) and check(i, j, k):  # k 未覆盖且与 i、j 共线，可以顺带覆盖
                                nxt |= 1 << k  # 把 k 一并标记为已覆盖
                        ans = min(ans, dfs(nxt) + 1)  # 一条直线覆盖 i、j 及同线点后递归，取最小值
                    if i == n - 1:  # 只剩最后一个未覆盖点：没有更大的 j 可配对
                        ans = min(ans, dfs(state | 1 << i) + 1)  # 单独用一条直线覆盖它
            return ans  # 返回该状态的最优解

        n = len(points)  # 点的个数 n（闭包在调用时才读取，所以放在 dfs 定义之后）
        return dfs(0)  # 从「一个点都没覆盖」开始搜索
