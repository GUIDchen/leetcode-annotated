# 题目：1941. 检查是否所有字符出现次数相同（Check if All Characters Have Equal Number of Occurrences）
# 思路：Counter 统计每个字符的出现次数，把次数集合用 set 去重；只剩一种次数就说明所有字符出现次数相同。
# 时间复杂度：O(n)；空间复杂度：O(σ)，σ 为字符种类数（小写字母至多 26），即 O(1)。
class Solution:  # LeetCode 约定的题解类
    def areOccurrencesEqual(self, s: str) -> bool:  # s 是待检查的字符串，题目保证非空
        return len(set(Counter(s).values())) == 1  # Counter(s) 统计各字符次数，values() 取出所有次数，set 去重后长度为 1 说明次数全相同
