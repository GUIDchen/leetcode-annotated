# 题目：2347. 最好的扑克手牌（Best Poker Hand）
# 思路：先用 pairwise 比较相邻花色判断同花；再用 Counter 统计点数频次，命中 3 张为三条、命中 2 张为对子，否则高牌。
# 时间复杂度：O(n)，n = 5；空间复杂度：O(1)，哈希表最多 5 个键。
class Solution:  # LeetCode 约定的题解类
    def bestHand(self, ranks: List[int], suits: List[str]) -> str:  # ranks 为点数，suits 为花色
        # 以下是原作者的等价写法，已被下一行的 pairwise 写法取代，保留原注释
        # if len(set(suits)) == 1:
        if all(a == b for a, b in pairwise(suits)):  # pairwise 生成相邻元素对，全部相等即五张同花
            return 'Flush'  # 同花最大，直接返回
        cnt = Counter(ranks)  # 统计每种点数出现的张数
        if any(v >= 3 for v in cnt.values()):  # 存在某点数出现 3 张或以上
            return 'Three of a Kind'  # 三条优先于对子
        if any(v == 2 for v in cnt.values()):  # 没有三条，但存在恰好两张同点数
            return 'Pair'  # 返回对子
        return 'High Card'  # 既非同花也无三条、对子，只剩高牌
