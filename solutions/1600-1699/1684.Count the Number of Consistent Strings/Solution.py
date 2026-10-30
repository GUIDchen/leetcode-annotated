# 题目：1684. 统计一致字符串的数目（Count the Number of Consistent Strings）
# 思路：把 allowed 转成集合，然后逐个单词判断其所有字符是否都落在集合内，用生成器表达式配合 sum 统计个数。
# 时间复杂度：O(|allowed| + Σ|word|)，每个字符只检查一次；空间复杂度：O(26)，集合大小不超过字母表。
class Solution:  # LeetCode 约定的题解类
    def countConsistentStrings(self, allowed: str, words: List[str]) -> int:  # allowed：允许的字符集合；words：待检查的单词；返回一致字符串的数目
        s = set(allowed)  # 转成集合后单次查找为 O(1)
        return sum(all(c in s for c in w) for w in words)  # 对每个单词 w，判断它的每个字符 c 是否都在集合 s 中；布尔值求和即为一致单词的数目
