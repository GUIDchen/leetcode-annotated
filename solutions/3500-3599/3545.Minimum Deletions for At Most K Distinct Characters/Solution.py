# 题目：3545. 不同字符数量最多为 K 时的最少删除数（Minimum Deletions for At Most K Distinct Characters）
# 思路：统计每个字母的出现次数后升序排序，保留出现次数最多的 K 种字母，其余字母的次数之和就是最少删除数。
# 时间复杂度：O(n + Σ log Σ)，Σ 为不同字符数（不超过 26）；空间复杂度：O(Σ)，即 O(1)。
class Solution:  # LeetCode 约定的题解类
    def minDeletion(self, s: str, k: int) -> int:  # s：输入字符串；k：允许保留的不同字符数量上限
        return sum(sorted(Counter(s).values())[:-k])  # 升序排序后去掉最大的 k 个计数，其余求和即为最少删除数
