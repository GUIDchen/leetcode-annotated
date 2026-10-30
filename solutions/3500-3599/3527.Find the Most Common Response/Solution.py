# 题目：3527. 找到最常见的回答（Find the Most Common Response）
# 思路：每天的相同回答只算一次，用集合去重后累计每个回答出现的天数；再遍历计数表，按「天数最多、同天数取字典序最小」选答案。
# 时间复杂度：O(L)，L 为所有回答的总字符数；空间复杂度：O(U)，U 为不同回答个数。
class Solution:  # LeetCode 约定的题解类
    def findCommonResponse(self, responses: List[List[str]]) -> str:  # responses 是每天的回答列表，返回出现天数最多的回答
        cnt = Counter()  # cnt[w] 记录回答 w 出现在多少天里
        for ws in responses:  # 逐天取出当天的回答列表
            for w in set(ws):  # 先按天去重，同一天里的重复回答只算一次
                cnt[w] += 1  # 该回答出现的天数加一
        ans = responses[0][0]  # 任意取一个候选作为初始答案
        for w, x in cnt.items():  # 遍历所有出现过的回答及其天数
            if cnt[ans] < x or (cnt[ans] == x and w < ans):  # 天数更多，或天数相同但字典序更小
                ans = w  # 更新最优回答
        return ans  # 返回出现天数最多且字典序最小的回答
