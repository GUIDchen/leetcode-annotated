# 题目：1230. 抛掷硬币（Toss Strange Coins）
# 思路：二维概率 DP，f[i][j] 表示前 i 枚硬币恰好 j 枚正面的概率；第 i 枚为反面乘 (1 - p) 保持 j，为正面乘 p 从 j-1 转移。
# 时间复杂度：O(n × target)，双重循环；空间复杂度：O(n × target)，DP 表规模。
class Solution:  # LeetCode 约定的题解类
    def probabilityOfHeads(self, prob: List[float], target: int) -> float:  # prob[i]：第 i 枚硬币正面的概率；target：需要的正面数，返回对应概率
        n = len(prob)  # n：硬币总数
        f = [[0] * (target + 1) for _ in range(n + 1)]  # DP 表：f[i][j] = 前 i 枚硬币恰好 j 枚正面的概率，两维多留一格免去边界判断
        f[0][0] = 1  # 初始化：0 枚硬币凑出 0 个正面的概率是 1
        for i, p in enumerate(prob, 1):  # 按顺序加入每枚硬币，i 从 1 开始，p 是该枚正面的概率
            for j in range(min(i, target) + 1):  # j 枚举当前正面数，上限是 i 与 target 的较小值
                f[i][j] = (1 - p) * f[i - 1][j]  # 这枚是反面：乘 (1 - p)，正面数不变
                if j:  # j 非 0 时才能讨论这枚是正面的情况
                    f[i][j] += p * f[i - 1][j - 1]  # 这枚是正面：乘 p，由「前 i-1 枚有 j-1 个正面」转移而来
        return f[n][target]  # 前 n 枚恰好 target 个正面的概率即答案
