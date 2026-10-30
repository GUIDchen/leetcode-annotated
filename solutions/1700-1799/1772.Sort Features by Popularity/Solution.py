# 题目：1772. 按受欢迎程度排列功能（Sort Features by Popularity）
# 思路：统计每个功能被多少个不同用户提到（同一反馈内先去重），再按热度稳定排序，热度相同时保持输入顺序。
# 时间复杂度：O(m·L + n log n)，m 为反馈条数、L 为单条反馈长度、n 为功能数；空间复杂度：O(m·L) 用于存词频。
class Solution:  # LeetCode 约定的题解类
    def sortFeatures(self, features: List[str], responses: List[str]) -> List[str]:  # features：待排序的功能名；responses：每个用户的反馈句子
        cnt = Counter()  # 计数器：功能名 → 被多少个不同用户提到
        for s in responses:  # 逐条处理每个用户的反馈句子
            for w in set(s.split()):  # 拆词并去重，保证同一用户重复提到只计一次
                cnt[w] += 1  # 该功能的提及用户数加一
        return sorted(features, key=lambda w: -cnt[w])  # 按热度降序排序（key 取负数、sorted 稳定），热度相同保持原顺序
