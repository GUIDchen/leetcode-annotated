# 题目：340. 至多包含 K 个不同字符的最长子串（Longest Substring with At Most K Distinct Characters）
# 核心思路：滑动窗口配合 Counter 计数，右边界逐个纳入字符，不同字符超过 k 时左边界右移一格收缩。
# 时间复杂度：O(n)，左右指针都只前进不回退；空间复杂度：O(min(n, σ))，计数器最多保存 k+1 个字符。
class Solution:  # LeetCode 约定的题解类
    def lengthOfLongestSubstringKDistinct(self, s: str, k: int) -> int:  # s 是输入字符串，k 是不同字符数上限，返回最长子串长度
        l = 0  # 滑动窗口左边界，初始为 0
        cnt = Counter()  # Counter 统计窗口内每个字符的出现次数
        for c in s:  # 右边界随遍历右移，把当前字符纳入窗口
            cnt[c] += 1  # 当前字符计数加一
            if len(cnt) > k:  # 窗口内不同字符种类超过 k，需要收缩左边界
                cnt[s[l]] -= 1  # 左边界字符计数减一
                if cnt[s[l]] == 0:  # 计数归零说明该字符已完全离开窗口
                    del cnt[s[l]]  # 从 Counter 中删除该键，让 len(cnt) 如实表示不同字符数
                l += 1  # 左边界右移一格
        return len(s) - l  # 剩下的后缀就是最长合法窗口，长度为 n - l
