# 题目：1967. 作为子字符串出现在单词中的字符串数目（Number of Strings That Appear as Substrings in Word）
# 思路：生成器里对每个模式串判断 `p in word` 得到布尔值，sum 把 True 当作 1 累加，一次表达式即得答案。
# 时间复杂度：O(sum(|p| * |word|))，每个模式一次子串匹配；空间复杂度：O(1)，不保存中间列表。
class Solution:  # LeetCode 约定的题解类
    def numOfStrings(self, patterns: List[str], word: str) -> int:  # patterns 是候选子串，word 是主串，返回命中个数
        return sum(p in word for p in patterns)  # 生成器逐项判断是否出现在 word 中，sum 把 True 计为 1
