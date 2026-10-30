# 3884. 双端字符匹配 / First Matching Character From Both Ends
# 核心思路：从左端枚举到中点，比较 s[i] 与对称位置 s[-1-i]，第一个相等的位置即为答案。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 定义题解类
    def firstMatchingIndex(self, s: str) -> int:  # 返回首尾对称位置字符相同的最小下标
        for i in range(len(s) // 2 + 1):  # 从左端枚举到中点
            if s[i] == s[-i - 1]:  # 与对称的最右端字符比较
                return i  # 找到最小的匹配下标
        return -1  # 不存在匹配则返回 -1
