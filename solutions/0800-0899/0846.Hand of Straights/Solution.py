# 题目：846. 一手顺子（Hand of Straights）
# 思路：按点数排序后贪心分组，遇到还有剩余的牌就强制以它开头，连续取 groupSize 张牌。
# 时间复杂度：O(n log n)，主要开销在排序；空间复杂度：O(n)，Counter 统计每个点数出现次数。
class Solution:  # LeetCode 约定的题解类
    def isNStraightHand(self, hand: List[int], groupSize: int) -> bool:  # hand 是手牌点数，groupSize 是每组顺子的长度；返回能否恰好分成若干组
        if len(hand) % groupSize:  # 牌数必须能被 groupSize 整除，否则分不完
            return False  # 余数非零，直接返回 False
        cnt = Counter(hand)  # 统计每个点数还剩多少张牌（Counter 由判题环境提供）
        for x in sorted(hand):  # 按点数从小到大遍历，依次安排每张牌
            if cnt[x]:  # 该点数还有剩余牌时，才需要以它开头组一条顺子
                for y in range(x, x + groupSize):  # 以 x 开头，向后取 groupSize 张连续牌
                    if cnt[y] == 0:  # 所需点数已经没有牌，凑不成顺子
                        return False  # 返回 False
                    cnt[y] -= 1  # 用掉点数 y 的一张牌
        return True  # 全部牌都成功分组，返回 True
