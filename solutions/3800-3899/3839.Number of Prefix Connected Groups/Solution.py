# 3839. 前缀连接组的数目 / Number of Prefix Connected Groups（中等）
# 核心思路：只对长度不小于 k 的单词取其前 k 个字符计数，最后统计出现次数大于 1 的前缀个数，即为可以成组的组数。
# 复杂度：时间 O(所有单词长度之和)，空间 O(不同前缀个数 * k)。
class Solution:  # LeetCode 要求的类名
    def prefixConnected(self, words: List[str], k: int) -> int:  # 返回可以成组的长度为 k 的前缀个数
        cnt = Counter()  # 统计每个长度 k 前缀出现的次数
        for w in words:  # 遍历所有单词
            if len(w) >= k:  # 只统计长度不小于 k 的单词（更短的无法取前缀）
                cnt[w[:k]] += 1  # 取出前 k 个字符作为键并计数
        return sum(v > 1 for v in cnt.values())  # 统计出现次数大于 1 的前缀个数即为组数
