# 题目：2185. 统计包含给定前缀的字符串（Counting Words With a Given Prefix）
# 思路：用 str.startswith 逐个判断单词是否以 pref 开头，生成器里的 True 计为 1，交给 sum 求和。
# 时间复杂度：O(m·n)，m 为单词个数、n 为前缀长度；空间复杂度：O(1)，生成器不额外占空间。
class Solution:  # LeetCode 约定的题解类
    def prefixCount(self, words: List[str], pref: str) -> int:  # words：单词列表；pref：待匹配前缀
        return sum(w.startswith(pref) for w in words)  # 生成器逐个判断是否以 pref 开头，True 记为 1 后求和
