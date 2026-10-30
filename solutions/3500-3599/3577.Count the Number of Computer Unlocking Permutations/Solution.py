# 题目：3577. 统计计算机解锁顺序排列数 / Count the Number of Computer Unlocking Permutations（中等）
# 核心思路：第 0 台计算机必须最先解锁，其它计算机都要求其复杂度严格小于它的复杂度才能解锁；因此只要存在 complexity[i] <= complexity[0] 就无解返回 0，否则第 i 台（1 到 n-1）能放在前 i 个位置中的任意一个，方案数为连乘 1*2*...*(n-1)，即 (n-1)!，过程中对 1e9+7 取模。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # 定义题解类
    def countPermutations(self, complexity: List[int]) -> int:  # 返回合法的解锁顺序排列数
        mod = 10**9 + 7  # 取模常数
        ans = 1  # 方案数，初始为 1
        for i in range(1, len(complexity)):  # 从第 1 台开始逐个统计
            if complexity[i] <= complexity[0]:  # 复杂度不严格大于第 0 台，第 0 台无法先被解锁
                return 0  # 无解
            ans = ans * i % mod  # 第 i 台有 i 个可选位置，累乘并取模
        return ans  # 返回方案数
