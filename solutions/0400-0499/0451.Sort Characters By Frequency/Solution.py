# 题目：451. 根据字符出现频率排序（Sort Characters By Frequency）
# 思路：用计数器统计每个字符的出现次数，再按次数降序排序，最后把每个字符重复其次数后拼接成结果串。
# 时间复杂度：O(n + k log k)，n 为串长、k 为不同字符数；空间复杂度：O(k)，计数器与排序结果。
class Solution:  # LeetCode 约定的题解类
    def frequencySort(self, s: str) -> str:  # s：待排序的字符串；返回按出现频率降序重排后的新串
        cnt = Counter(s)  # 统计每个字符的出现次数（Counter 由判题环境提供，无需 import）
        return ''.join(c * v for c, v in sorted(cnt.items(), key=lambda x: -x[1]))  # 按次数从大到小排序后，每个字符重复其次数，再拼成一个字符串
