# 题目：914. 卡牌分组（X of a Kind in a Deck of Cards）
# 核心思路：用 Counter 统计每个牌面的频次，再求所有频次的最大公约数；公约数 >= 2 说明每种牌都能按同一组大小切分完。
# 时间复杂度：O(n + m log C)；空间复杂度：O(m)，m 为不同牌面数。
class Solution:  # 题解类
    def hasGroupsSizeX(self, deck: List[int]) -> bool:  # 判断整副牌能否按牌面分组，每组大小 X >= 2 且各组大小相同
        cnt = Counter(deck)  # 统计每个牌面出现的次数
        return reduce(gcd, cnt.values()) >= 2  # 所有频次的最大公约数 >= 2 才能同时整除每种牌的分组
