# 题目：3223. 操作后字符串的最短长度（Minimum Length of String After Operations）
# 思路：一次操作会删掉某个字符左右各一个同字符，所以每个字符的个数只按奇偶性收缩：奇数次最终留 1 个，偶数次最终留 2 个。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)，最多 26 个计数。
class Solution:  # LeetCode 约定的题解类
    def minimumLength(self, s: str) -> int:  # 返回操作后字符串的最短长度
        cnt = Counter(s)  # 统计每个字符出现次数（Counter 由判题环境提供，无需 import）
        return sum(1 if x & 1 else 2 for x in cnt.values())  # 出现奇数次留 1 个、偶数次留 2 个，求和即为最短长度
