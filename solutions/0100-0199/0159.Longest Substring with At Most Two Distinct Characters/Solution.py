# 题目：159. 至多包含两个不同字符的最长子串（Longest Substring with At Most Two Distinct Characters）
# 思路：滑动窗口。右指针逐个扩窗并计数，字符种类超过 2 时左指针收缩，每次收缩后更新答案。
# 时间复杂度：O(n)，i、j 都只单调右移；空间复杂度：O(1)，计数器最多保存 3 种字符。
class Solution:  # LeetCode 约定的题解类
    def lengthOfLongestSubstringTwoDistinct(self, s: str) -> int:  # s 是输入字符串，返回至多含两种字符的最长子串长度
        cnt = Counter()  # 计数器：记录窗口内每种字符的出现次数
        ans = j = 0  # ans 保存历史最大长度；j 是窗口左边界（右边界由循环变量 i 给出）
        for i, c in enumerate(s):  # 枚举右边界 i，同时拿到字符 c
            cnt[c] += 1  # 把新字符计入窗口
            while len(cnt) > 2:  # 字符种类超过 2 时窗口不合法，需要收缩
                cnt[s[j]] -= 1  # 左边界字符的计数减一
                if cnt[s[j]] == 0:  # 该字符在窗口内已经消失（计数归零）
                    cnt.pop(s[j])  # 从计数器中删除它，len(cnt) 才会等于真实种类数
                j += 1  # 左边界右移一位
            ans = max(ans, i - j + 1)  # 此时窗口合法，用窗口长度 i-j+1 更新答案
        return ans  # 返回记录到的最大长度
