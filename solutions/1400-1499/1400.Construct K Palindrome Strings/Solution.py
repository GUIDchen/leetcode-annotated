# 题目：1400. 构造 K 个回文字符串（Construct K Palindrome Strings）
# 思路：先判长度 len(s) >= k，再统计「奇数频次字符个数」；k 个回文段最多容纳 k 个奇数字符，故奇数个数 x <= k 即可行。
# 时间复杂度：O(n)，Counter 线性统计；空间复杂度：O(σ)，σ 为字符种类数（本题不超过 26）。
class Solution:  # LeetCode 约定的题解类
    def canConstruct(self, s: str, k: int) -> bool:  # s 为输入字符串，k 为要构造的回文串个数
        if len(s) < k:  # 字符数少于段数，必然切不出 k 个非空回文串
            return False  # 直接返回不可能
        cnt = Counter(s)  # 统计每个字符的出现次数（判题环境已提供 Counter，无需 import）
        return sum(v & 1 for v in cnt.values()) <= k  # v & 1 取频次奇偶性，奇数种类数不超过 k 即可行
