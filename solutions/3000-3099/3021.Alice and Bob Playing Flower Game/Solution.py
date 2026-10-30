# 题目：3021. Alice 和 Bob 玩鲜花游戏（Alice and Bob Playing Flower Game）
# 思路：每回合拿走 x+y 朵花，Alice 后手获胜当且仅当 x+y 为奇数，即 x、y 一奇一偶；分别统计两段区间的奇数、偶数个数后交叉相乘。
# 时间复杂度：O(1)，只做常数次算术；空间复杂度：O(1)，只用 4 个变量。
class Solution:  # LeetCode 约定的题解类
    def flowerGame(self, n: int, m: int) -> int:  # n 是 x 的上界，m 是 y 的上界，返回 Alice 获胜的回合数
        a1 = (n + 1) // 2  # a1：1..n 中奇数的个数
        b1 = (m + 1) // 2  # b1：1..m 中奇数的个数
        a2 = n // 2  # a2：1..n 中偶数的个数
        b2 = m // 2  # b2：1..m 中偶数的个数
        return a1 * b2 + a2 * b1  # 奇数×偶数 + 偶数×奇数，即 x+y 为奇数的组合数
