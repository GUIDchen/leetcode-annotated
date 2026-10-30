# 题目：1066. 校园自行车分配 II（Campus Bikes II）
# 思路：状态压缩 DP，f[i][j] 表示前 i 个工人骑走自行车集合 j 的最小代价，枚举第 i 个工人骑的车 k 转移。
# 时间复杂度：O(n · 2^m · m)；空间复杂度：O(n · 2^m)，n 为工人数、m 为自行车数。
class Solution:  # LeetCode 约定的题解类
    def assignBikes(self, workers: List[List[int]], bikes: List[List[int]]) -> int:  # workers/bikes：各点坐标 [x, y]；返回所有工人都分到车的最小曼哈顿距离和
        n, m = len(workers), len(bikes)  # 工人数 n 与自行车数 m，题目保证 m >= n
        f = [[inf] * (1 << m) for _ in range(n + 1)]  # f[i][j]：前 i 个工人使用自行车集合 j（位掩码）时的最小总距离，inf 表示不可达
        f[0][0] = 0  # 边界：0 个工人、车集合为空，代价为 0
        for i, (x1, y1) in enumerate(workers, 1):  # 逐个考虑工人，编号从 1 开始同时取出其坐标 (x1, y1)
            for j in range(1 << m):  # 枚举这 i 个工人用到的自行车集合 j（共 2^m 种）
                for k, (x2, y2) in enumerate(bikes):  # 枚举第 i 个工人具体骑哪辆车，同时取出车坐标 (x2, y2)
                    if j >> k & 1:  # 车 k 必须属于集合 j，转移才成立
                        f[i][j] = min(  # 从「去掉车 k 的前 i-1 个工人状态」加上这一步的曼哈顿距离来更新
                            f[i][j],  # 原有的更优方案保留下来
                            f[i - 1][j ^ (1 << k)] + abs(x1 - x2) + abs(y1 - y2),  # 新方案：前 i-1 个工人用掉其余车，第 i 个工人骑 k 号车
                        )  # min 调用结束
        return min(f[n])  # n 个工人恰占用 n 辆车，所有集合的最小值即全局最优
