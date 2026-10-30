# 题目：424. 替换后的最长重复字符（Longest Repeating Character Replacement）
# 思路：滑动窗口内维护出现次数最多的字符计数 mx，当窗口长度减 mx 大于 k 时左指针右移一格，窗口只增不减，最终长度即答案。
# 时间复杂度：O(n)，每个字符最多进出窗口一次；空间复杂度：O(1)，字符计数最多 26 个键。
class Solution:  # LeetCode 题解类
    def characterReplacement(self, s: str, k: int) -> int:  # s：大写字母组成的字符串；k：最多可替换的字符数
        cnt = Counter()  # 记录当前窗口内每个字符出现的次数
        l = mx = 0  # l：窗口左边界；mx：窗口内同一字符的最大出现次数
        for r, c in enumerate(s):  # r 是窗口右边界，c 是刚进入窗口的字符
            cnt[c] += 1  # 新字符入窗，计数加一
            mx = max(mx, cnt[c])  # 更新窗口内最高频字符的计数
            if r - l + 1 - mx > k:  # 窗口长度减去 mx 就是需要替换的字符数，超过 k 说明窗口不合法
                cnt[s[l]] -= 1  # 把左边界字符移出窗口
                l += 1  # 左边界右移一格，窗口长度不再增长
        return len(s) - l  # 循环结束时 n - l 就是历史最长合法窗口的长度
