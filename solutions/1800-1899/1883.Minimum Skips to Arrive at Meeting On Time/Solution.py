# 题目：1883. 准时抵达会议现场的最小跳过休息次数（Minimum Skips to Arrive at Meeting On Time）
# 思路：动态规划，f[i][j] 表示走完前 i 段且跳过 j 次等待的最小耗时；每段在「向上取整到整点」与「跳过等待」两种转移里取较小值。
# 时间复杂度：O(n^2)，两层循环；空间复杂度：O(n^2)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minSkips(self, dist: List[int], speed: int, hoursBefore: int) -> int:  # dist 是各段距离，speed 是速度，hoursBefore 是时限
        n = len(dist)  # 路段数量，也是 DP 规模
        f = [[inf] * (n + 1) for _ in range(n + 1)]  # DP 表全部初始化为 inf，表示不可达
        f[0][0] = 0  # 边界：一段没走、跳过 0 次，耗时 0
        eps = 1e-8  # 浮点误差容限，防止向上取整把整数误加一
        for i, x in enumerate(dist, 1):  # 从 1 开始枚举前 i 段，x 是第 i 段的距离
            for j in range(i + 1):  # 枚举跳过次数，最多不超过已走段数
                if j < i:  # 本次不跳过：需要等到整点再继续
                    f[i][j] = min(f[i][j], ceil(f[i - 1][j] + x / speed - eps))  # 减 eps 后向上取整，模拟整点等待
                if j:  # 本次跳过等待：上一状态只跳过 j - 1 次
                    f[i][j] = min(f[i][j], f[i - 1][j - 1] + x / speed)  # 直接累加耗时，不做取整
        for j in range(n + 1):  # 从少到多寻找最小的可行跳过次数
            if f[n][j] <= hoursBefore + eps:  # 加 eps 抵消浮点误差后判断是否准时
                return j  # 第一个满足条件的 j 即答案
        return -1  # 全部方案都迟到，返回 -1
