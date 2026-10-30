# 题目：3. 无重复字符的最长子串（Longest Substring Without Repeating Characters）
# 思路：滑动窗口 + 计数器，右指针逐字符入窗；某字符出现两次时移动左指针收缩，直到窗口重新合法。
# 时间复杂度：O(n)，每个字符最多进出窗口各一次；空间复杂度：O(1)，计数器的键数不超过字符集大小。
class Solution:  # LeetCode 约定的题解类
    def lengthOfLongestSubstring(self, s: str) -> int:  # s 为输入字符串，返回无重复字符子串的最大长度
        cnt = Counter()  # 计数器：记录每个字符在当前窗口内出现的次数
        ans = l = 0  # ans 保存最大长度；l 是窗口左边界（右边界由 enumerate 给出）
        for r, c in enumerate(s):  # r 为右边界下标，c 为右边界字符
            cnt[c] += 1  # 新字符入窗，计数加一
            while cnt[c] > 1:  # c 在窗口内出现两次，窗口失效
                cnt[s[l]] -= 1  # 左边界字符移出窗口
                l += 1  # 左指针右移，继续收缩
            ans = max(ans, r - l + 1)  # 当前窗口长度为 r - l + 1，用它更新答案
        return ans  # 返回最大长度
