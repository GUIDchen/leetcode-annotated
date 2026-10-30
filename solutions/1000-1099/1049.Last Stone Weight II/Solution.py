# 题目：1049. 最后一块石头的重量 II（Last Stone Weight II）
# 思路：等价于把石头分成两堆使重量差最小，转化为 0-1 背包：在容量 sum/2 内求能凑出的最大重量，答案为 sum - 2*背包值。
# 时间复杂度：O(m * sum)，m 为石头数；空间复杂度：O(m * sum)，使用二维 dp 表。
class Solution:  # LeetCode 约定的题解类
    def lastStoneWeightII(self, stones: List[int]) -> int:  # stones：石头重量列表
        s = sum(stones)  # 总重量：分成两堆后答案就是两堆重量之差的绝对值
        m, n = len(stones), s >> 1  # m 为石头数；n 是背包容量，取总和的一半向下取整
        dp = [[0] * (n + 1) for _ in range(m + 1)]  # dp[i][j]：前 i 块石头能凑出不超过 j 的最大重量
        for i in range(1, m + 1):  # 逐块考虑石头
            for j in range(n + 1):  # 枚举所有可能的容量
                dp[i][j] = dp[i - 1][j]  # 不选当前石头时直接继承上一行
                if stones[i - 1] <= j:  # 容量足够放下当前石头
                    dp[i][j] = max(  # 在「不选」和「选」两种方案中取更大的重量
                        dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]  # 选它之后，剩余容量 j-stones[i-1] 由前 i-1 块石头凑
                    )  # 比较表达式结束
        return s - 2 * dp[-1][-1]  # 两堆之差即 s - 2*最接近一半的可凑重量
