# 题目：2427. 公因子的数目（Number of Common Factors）
# 核心思路：a、b 的公因子恰好是最大公因数 g = gcd(a, b) 的全部因子，所以枚举 1..g 统计能整除 g 的个数即可。
# 时间复杂度：O(g)，最坏 O(min(a, b))；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def commonFactors(self, a: int, b: int) -> int:  # a、b 是两个正整数，返回公因子的数目
        g = gcd(a, b)  # 最大公因数：它的因子集合就是公因子集合
        return sum(g % x == 0 for x in range(1, g + 1))  # 生成器表达式逐个判断能否整除 g，sum 把 True 计为 1 并求和
