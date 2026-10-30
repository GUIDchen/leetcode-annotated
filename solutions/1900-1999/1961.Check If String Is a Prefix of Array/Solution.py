# 题目：1961. 检查字符串是否为数组前缀（Check If String Is a Prefix of Array）
# 思路：累加 words 中每个词的长度 m，一旦 m 等于 len(s) 就拼接前 i+1 个词与 s 比较；长度已超出的情形由早退自然排除。
# 时间复杂度：O(L)，L 为拼接串长度；空间复杂度：O(L)，join 需要一份临时副本。
class Solution:  # LeetCode 约定的题解类
    def isPrefixString(self, s: str, words: List[str]) -> bool:  # s 是目标字符串，words 是候选词数组
        n, m = len(s), 0  # n 是 s 的长度，m 记录已拼词的总长度
        for i, w in enumerate(words):  # i 是当前词的下标，w 是当前词
            m += len(w)  # 累加当前词的长度
            if m == n:  # 总长度刚好等于 s 的长度，说明前缀到此为止
                return "".join(words[: i + 1]) == s  # 比较前 i+1 个词拼接的结果是否与 s 相等
        return False  # 词全部用完长度仍不足，s 太长，不是前缀
