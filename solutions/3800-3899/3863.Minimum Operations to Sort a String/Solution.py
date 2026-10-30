# 题目：3863. 将一个字符串排序的最小操作次数（Minimum Operations to Sort a String）
# 思路：分类讨论——已有序返回 0；长度为 2 无法选出真子串返回 -1；最小字符在首位或最大字符在末位 1 次；极值出现在中间 2 次；否则 3 次。
# 时间复杂度：O(n)，各分支都是线性扫描；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, s: str) -> int:  # 每次可以排序一个真子串，返回使 s 非降的最少操作次数
        if all(a <= b for a, b in pairwise(s)):  # 逐对检查相邻字符是否非降
            return 0  # 已经有序，不需要任何操作
        if len(s) == 2:  # 长度为 2 时，可选的子串只能覆盖单个字符
            return -1  # 无法完成排序
        mn, mx = min(s), max(s)  # 全局最小与最大字符
        if s[0] == mn or s[-1] == mx:  # 最小已在首位（排序后缀）或最大已在末位（排序前缀）
            return 1  # 一次操作即可排好
        if any(c in [mn, mx] for c in s[1:-1]):  # 中间位置出现极值字符，可先把它排到端点
            return 2  # 两次操作即可
        return 3  # 其余情况三次操作足够
