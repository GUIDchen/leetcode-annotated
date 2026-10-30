# 题目：692. 前 K 个高频单词（Top K Frequent Words）
# 思路：Counter 统计词频，再用排序键（频次取负、单词本身）一次排序，最后切片取前 k 个。
# 时间复杂度：O(m log m)，m 为不同单词数；空间复杂度：O(m)，存词频表与排序结果。
class Solution:
    def topKFrequent(self, words: List[str], k: int) -> List[str]:  # words 是单词列表，k 是要取出的个数，返回按频率降序（同频按字典序升序）的前 k 个单词
        cnt = Counter(words)  # 统计每个单词出现的次数
        return sorted(cnt, key=lambda x: (-cnt[x], x))[:k]  # 排序键 -cnt[x] 让高频在前，x 在频次相同时保证字典序升序；切片取前 k 个
