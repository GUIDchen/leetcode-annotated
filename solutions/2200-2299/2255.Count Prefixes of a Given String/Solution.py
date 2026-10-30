# 题目：2255. 统计是给定字符串前缀的字符串数目（Count Prefixes of a Given String）
# 思路：用生成器表达式逐个判断 words 中的字符串是否为 s 的前缀，startswith 返回布尔值，sum 把 True 当作 1 累加得到个数。
# 时间复杂度：O(Σ|w|)，每个单词只与 s 的前 |w| 个字符比较；空间复杂度：O(1)，生成器不建中间列表。
class Solution:  # LeetCode 约定的题解类
    def countPrefixes(self, words: List[str], s: str) -> int:  # words 是候选前缀列表，s 是被检查的字符串
        return sum(s.startswith(w) for w in words)  # 逐个判断 w 是否为 s 的前缀，布尔值求和即答案
