# 题目：3325. 字符至少出现 K 次的子字符串 I（Count Substrings With K-Frequency Characters I）
# 思路：滑动窗口。cnt 记录窗口内各字符出现次数，右端入窗后若该字符达到 k 次就收缩左端，此时起点早于 l 的子串全部合法。
# 时间复杂度：O(n)，每个字符最多进出窗口各一次；空间复杂度：O(1)，计数器里最多 26 个字母。
class Solution:  # LeetCode 约定的题解类
    def numberOfSubstrings(self, s: str, k: int) -> int:  # s 为只含小写字母的字符串，k 是要求的最低出现次数
        cnt = Counter()  # 记录窗口内各字符出现次数，缺失的键按 0 处理
        ans = l = 0  # ans 累计答案，l 是窗口左边界，链式赋值让两者都从 0 开始
        for c in s:  # 逐个字符作为窗口右端，c 为当前入窗字符
            cnt[c] += 1  # 当前字符入窗，计数加一
            while cnt[c] >= k:  # c 在窗口内达到 k 次说明窗口不合法，必须收缩左端
                cnt[s[l]] -= 1  # 左端字符出窗，计数减一
                l += 1  # 左边界右移一位
            ans += l  # 循环结束时窗口内没有字符达标，起点在 [0, l-1] 的子串都合法，共 l 个
        return ans  # 返回合法子串总数
