# 题目：3137. K 周期字符串需要的最少操作次数（Minimum Number of Operations to Make Word K-Periodic）
# 思路：把 word 按长度 k 切成 n/k 个块，统计出现次数最多的那种块，其余块逐个改成它即可。
# 时间复杂度：O(n)，每个块只切一次并计数；空间复杂度：O(n/k)，哈希表最多保存 n/k 种不同的块。
class Solution:  # LeetCode 约定的题解类
    def minimumOperationsToMakeKPeriodic(self, word: str, k: int) -> int:  # word 是原串，k 是周期块的长度
        n = len(word)  # 记录原串长度
        return n // k - max(Counter(word[i : i + k] for i in range(0, n, k)).values())  # 切出每个块并计数，取最大频次，总块数减去它即为最少操作次数
