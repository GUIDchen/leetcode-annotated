# 题目：2073. 买票需要的时间（Time Needed to Buy Tickets）
# 思路：第 k 个人买完 tickets[k] 张票之前，它前面（含自己）每人最多贡献 tickets[k] 张，它后面每人最多贡献 tickets[k] - 1 张，逐项取 min 累加。
# 时间复杂度：O(n)，只遍历一遍数组；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:  # tickets 是每个人的需求张数，k 是我们关注的人的下标
        ans = 0  # 累计卖出的票数，即总耗时（每卖一张票 1 秒）
        for i, x in enumerate(tickets):  # 同时取得下标 i 和该人的需求张数 x
            ans += min(x, tickets[k] if i <= k else tickets[k] - 1)  # i <= k 的人最多买 tickets[k] 张，i > k 的人最多买 tickets[k] - 1 张，取较小值累加
        return ans  # 返回总耗时
