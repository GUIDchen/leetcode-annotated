# 题目：2188. 完成比赛的最少时间（Minimum Time to Finish the Race）
# 思路：先用 while 对每种轮胎预处理「连续跑 j 圈」的最短耗时（单圈耗时超过换胎+首圈即停止，故 j <= 17），再按圈数做完全背包式 DP。
# 时间复杂度：O(T·18 + numLaps·18)；空间复杂度：O(18 + numLaps)。
class Solution:  # LeetCode 约定的题解类
    def minimumFinishTime(  # tires：每种轮胎的(首圈耗时, 倍率)；changeTime：换胎耗时；numLaps：需要跑的圈数
        self, tires: List[List[int]], changeTime: int, numLaps: int  # 续行：三个参数的类型与含义同上
    ) -> int:  # 返回值：跑完所有圈的最短时间
        cost = [inf] * 18  # cost[j]：同一套胎连续跑 j 圈的最短耗时
        for f, r in tires:  # 枚举每种轮胎：f 首圈耗时，r 倍率
            i, s, t = 1, 0, f  # i 当前圈数，s 累计耗时，t 当前这一圈的耗时
            while t <= changeTime + f:  # 单圈耗时超过「换胎+首圈」时继续跑就不划算，停止
                s += t  # 累计连续跑 i 圈的总耗时
                cost[i] = min(cost[i], s)  # 更新「连续跑 i 圈的最短耗时」
                t *= r  # 下一圈耗时按倍率增长
                i += 1  # 圈数加一
        f = [inf] * (numLaps + 1)  # f[i]：跑完前 i 圈的最小总耗时（含换胎）
        f[0] = -changeTime  # 起点：0 圈还没换过胎，先抵消第一次换胎时间
        for i in range(1, numLaps + 1):  # 从小到大递推每一圈的答案
            for j in range(1, min(18, i + 1)):  # 枚举最后一段连续跑的圈数 j，最多 17 圈
                f[i] = min(f[i], f[i - j] + cost[j])  # 用「前 i-j 圈 + 这一段的 j 圈」转移
            f[i] += changeTime  # 这一段开始前要换一次胎，统一补上换胎耗时
        return f[numLaps]  # 返回跑完 numLaps 圈的最小耗时
