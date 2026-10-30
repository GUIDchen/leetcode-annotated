# 题目：818. 赛车（Race Car）
# 思路：动态规划，dp[i] 表示到达位置 i 的最少指令数。i 恰为 2^k-1 时答案就是 k；否则先冲过头折返，或先到 2^(k-1)-1 再反向、前进、反向，取最小。
# 时间复杂度：O(target·log target)；空间复杂度：O(target)，dp 列表。
class Solution:  # LeetCode 约定的题解类
    def racecar(self, target: int) -> int:  # target：要到达的目标位置
        dp = [0] * (target + 1)  # dp[i] 表示到达位置 i 的最少指令数，先全部置 0
        for i in range(1, target + 1):  # 按位置从小到大递推
            k = i.bit_length()  # i 的二进制位数 k，代表加速次数所在的量级
            if i == 2**k - 1:  # i 恰好等于 2^k-1：连续 k 次 A 就能到达
                dp[i] = k  # 记录对应的指令数 k
                continue  # 已是最优，跳过其它转移
            dp[i] = dp[2**k - 1 - i] + k + 1  # 方案一：冲过头到 2^k-1 再反向，多花一条 R 指令
            for j in range(k - 1):  # 方案二：枚举掉头时走到的位置，尝试更优解
                dp[i] = min(dp[i], dp[i - (2 ** (k - 1) - 2**j)] + k - 1 + j + 2)  # 转移：k-1 次 A 到 2^(k-1)-1，再 R、再 j 次 A、再 R，指令数为 k-1+j+2
        return dp[target]  # 返回到达目标位置的最少指令数
