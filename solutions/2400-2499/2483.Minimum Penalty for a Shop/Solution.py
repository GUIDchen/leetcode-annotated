# 题目：2483. 商店的最少代价（Minimum Penalty for a Shop）
# 思路：先假设 0 点关门，代价是全部 'Y' 的个数；之后逐小时把关门时刻右移，'N' 让代价加 1、'Y' 让代价减 1，取最小代价，只在严格更小时更新以保证并列时保留最早时刻。
# 时间复杂度：O(n)，一次计数加一次遍历；空间复杂度：O(1)，只用常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def bestClosingTime(self, customers: str) -> int:  # customers：每小时 'Y'/'N'；返回代价最小的最早关门时刻
        ans = 0  # 最优关门时刻，先假设 0 点关门
        mn = cost = customers.count("Y")  # 0 点关门的代价 = 所有 'Y' 都进不了店；同时记下当前最小代价
        for j, c in enumerate(customers, 1):  # j 从 1 开始枚举关门时刻，c 是刚纳入营业的那一小时
            cost += 1 if c == "N" else -1  # 'N' 多一个空转代价 +1，'Y' 少一个被拒代价 -1
            if cost < mn:  # 严格小于才能保证并列时保留更早的时刻
                ans, mn = j, cost  # 同时更新最优时刻与最小代价
        return ans  # 返回结果
