# 题目：3090. 每个字符最多出现两次的最长子字符串（Maximum Length Substring With Two Occurrences）
# 思路：滑动窗口；右指针逐字符扩张并计数，某字符超过 2 次时移动左指针收缩，过程中记录窗口最大长度。
# 时间复杂度：O(n)，每个字符至多被左右指针各访问一次；空间复杂度：O(1)，字典最多存 26 个字母的计数。
class Solution:  # LeetCode 约定的题解类
    def maximumLengthSubstring(self, s: str) -> int:  # s 为输入字符串，返回「每个字符至多出现两次」的最长子串长度
        ans = l = 0  # ans 记录答案，l 是滑动窗口左端（两者同时初始化为 0）
        cnt = defaultdict(int)  # 窗口内字符计数，defaultdict 让未出现的字符默认计数为 0
        for r, c in enumerate(s):  # r 是窗口右端，c 是当前字符
            cnt[c] += 1  # 新字符进入窗口，计数加一
            while cnt[c] > 2:  # 该字符出现超过 2 次，窗口不再合法，需要收缩
                cnt[s[l]] -= 1  # 左端字符移出窗口，计数减一
                l += 1  # 左指针右移一位
            ans = max(ans, r - l + 1)  # 当前窗口合法，用其长度更新答案
        return ans  # 返回最长合法子串长度
