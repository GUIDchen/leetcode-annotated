# 题目：2260. 必须拿起的最小连续卡牌数（Minimum Consecutive Cards to Pick Up）
# 思路：一次遍历，用字典记录每种卡牌上次出现的下标；遇到出现过的卡牌就用两下标之差算出区间长度，全局取最小值。
# 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，字典最多保存 n 种卡牌。
class Solution:  # LeetCode 约定的题解类
    def minimumCardPickup(self, cards: List[int]) -> int:  # cards 是卡牌数组，返回必须拿起的最少卡牌张数
        last = {}  # 字典：卡牌值 → 该卡牌最近一次出现的下标
        ans = inf  # 用正无穷作哨兵，表示「还没有找到重复卡牌」
        for i, x in enumerate(cards):  # 同时取得下标 i 和卡牌值 x
            if x in last:  # 这张牌以前出现过，才能配对成一段连续区间
                ans = min(ans, i - last[x] + 1)  # 区间长度 = 下标差 + 1，保留更短的
            last[x] = i  # 把当前位置记为这张牌的最新下标
        return -1 if ans == inf else ans  # 哨兵未变说明没有重复卡牌，按题意返回 -1
