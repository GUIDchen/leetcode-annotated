# 题目：748. 最短补全词（Shortest Completing Word）
# 核心思路：用 Counter 统计牌照里（忽略大小写）的字母频次，遍历 words 逐个比较覆盖关系，记录其中最短的合格单词。
# 时间复杂度：O(L + Σ|w|)，L 为牌照长度；空间复杂度：O(1)，计数器最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def shortestCompletingWord(self, licensePlate: str, words: List[str]) -> str:  # licensePlate 是牌照串，words 是候选单词列表
        cnt = Counter(c.lower() for c in licensePlate if c.isalpha())  # 生成器只保留字母并统一小写，Counter 据此统计每个字母出现次数
        ans = None  # 记录目前最短的补全词，None 表示还没有候选
        for w in words:  # 按输入顺序检查每个单词
            if ans and len(w) >= len(ans):  # 已有答案且当前单词不严格更短，直接略过
                continue  # 跳到下一个单词
            t = Counter(w)  # 当前单词的字母频次
            if all(v <= t[c] for c, v in cnt.items()):  # 牌照所需的每个字母都被覆盖，这个单词就是合格的补全词
                ans = w  # 更新最短补全词
        return ans  # 返回结果，题目保证至少存在一个补全词
