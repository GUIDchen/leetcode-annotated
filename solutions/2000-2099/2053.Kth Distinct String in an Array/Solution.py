# 题目：2053. 数组中第 K 个独一无二的字符串（Kth Distinct String in an Array）
# 思路：先用 Counter 统计每个字符串的出现次数，再按原数组顺序扫描，数到第 k 个出现次数为 1 的字符串即为答案。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，Counter 保存不同字符串的出现次数。
class Solution:  # 题解类
    def kthDistinct(self, arr: List[str], k: int) -> str:  # arr 是字符串数组，k 是要求的第 k 个独一无二字符串
        cnt = Counter(arr)  # 统计每个字符串的出现次数
        for s in arr:  # 按原顺序扫描，保证“第 k 个”的顺序性
            if cnt[s] == 1:  # 只统计出现次数为 1 的字符串
                k -= 1  # 独一无二的计数减一
                if k == 0:  # 减到 0 就找到答案
                    return s  # 返回第 k 个独一无二的字符串
        return ""  # 数量不足，按题目要求返回空串
