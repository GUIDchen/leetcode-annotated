# 题目：1170. 比较字符串最小字母出现频次（Compare Strings by Frequency of the Smallest Character）
# 思路：先算每个单词的 f 值并排序，再对每个查询串算 f 值，用 bisect_right 数出单词中 f 值严格更大的个数（n 减去该位置）。
# 时间复杂度：O(|words|·L + |words| log |words| + |queries|·L log |words|)；空间复杂度：O(|words|)。
class Solution:  # 题解类
    def numSmallerByFrequency(self, queries: List[str], words: List[str]) -> List[int]:  # 对每个查询串，统计有多少个单词的 f 值严格大于它的 f 值
        def f(s: str) -> int:  # 内部函数 f：求题目定义的最小字母出现频次
            cnt = Counter(s)  # 统计每个字符出现次数
            return next(cnt[c] for c in ascii_lowercase if cnt[c])  # 按字母表顺序找到第一个出现过的字母并返回它的频次

        n = len(words)  # 单词个数
        nums = sorted(f(w) for w in words)  # 计算所有单词的 f 值并升序排序
        return [n - bisect_right(nums, f(q)) for q in queries]  # 二分出第一个大于 f(q) 的位置，n 减去它就是严格大于的个数
