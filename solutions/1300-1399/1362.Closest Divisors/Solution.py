# 题目：1362. 最接近的因数（Closest Divisors）
# 思路：答案一定来自 num+1 或 num+2；从平方根向下找第一个因子，此时这对因数最接近，两候选再比差值取更小者。
# 时间复杂度：O(√num)，两次枚举到平方根；空间复杂度：O(1)，不计返回的列表。
class Solution:  # LeetCode 约定的题解类
    def closestDivisors(self, num: int) -> List[int]:  # num 是给定的正整数，返回最接近的一对因数
        def f(x):  # 辅助函数 f：求 x 的一对最接近的因数
            for i in range(int(sqrt(x)), 0, -1):  # 从 ⌊√x⌋ 向下枚举，越靠近平方根因数对越接近
                if x % i == 0:  # 找到 x 的一个因子 i
                    return [i, x // i]  # 返回这对因数（i 较小，x // i 较大）

        a = f(num + 1)  # 候选一：num+1 的最接近因数对
        b = f(num + 2)  # 候选二：num+2 的最接近因数对
        return a if abs(a[0] - a[1]) < abs(b[0] - b[1]) else b  # 比较差值，返回更接近的那一对
