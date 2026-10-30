# 4027. 电梯请求 III / Elevator Requests III
# 核心思路：状压 DP，f[mask][j] 表示已处理集合 mask、最后处理请求 j 时的最早完成时间，转移时取“移动后的时刻”与“请求 j 的开放时间”的较大者。
# 复杂度：时间 O(2^m · m^2)，空间 O(2^m · m)（m 为请求数量）。
class Solution:  # 题解类定义
    def elevatorRequests(self, n: int, start: int, requests: list[list[int]]) -> int:  # 返回服务完所有请求所需的最短总时间
        m = len(requests)  # 请求的数量
        f = [[0] * m for _ in range(1 << m)]  # f[mask][j]：已服务集合为 mask、且最后服务的是请求 j 时的最早完成时间
        for i in range(1 << m):  # 枚举所有已服务集合（状压状态）
            for j in range(m):  # 枚举最后服务的那一个请求
                if i >> j & 1:  # 只有当 j 属于集合 i 时，该状态才存在
                    f[i][j] = inf  # 先置为无穷大，表示尚未松弛
                    i0 = i ^ (1 << j)  # 去掉 j 之后的前一状态
                    if i0 == 0:  # 前驱状态为空，说明 j 是第一个被服务的请求
                        d = abs(start - requests[j][1])  # 从起点 start 移动到请求 j 所在楼层的时间
                        f[i][j] = min(f[i][j], max(d, requests[j][0]))  # 最早完成时间 = max(到达时刻, 请求开放时间)
                    else:  # 否则需要从上一个被服务的请求转移过来
                        for j0 in range(m):  # 枚举前一个被服务的请求 j0
                            if j0 != j and (i >> j0 & 1):  # j0 必须不同于 j，且已经包含在集合 i 中
                                d = abs(requests[j0][1] - requests[j][1])  # 请求 j0 与请求 j 所在楼层之间的移动时间
                                f[i][j] = min(  # 用 j0 的完成时刻松弛当前状态
                                    f[i][j], max(f[i0][j0] + d, requests[j][0])  # 完成时刻与请求开放时间取最大值
                                )  # 结束本次松弛
        return min(f[(1 << m) - 1][j] for j in range(m))  # 取所有收尾方式中的最小值作为答案
