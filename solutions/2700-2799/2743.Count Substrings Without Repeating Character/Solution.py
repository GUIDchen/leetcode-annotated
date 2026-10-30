# 题目：2743. 计算没有重复字符的子字符串数量（Count Substrings Without Repeating Character）
# 核心思路：滑动窗口加计数器，窗口内始终保持无重复字符，以 i 结尾的合法子串个数正好等于窗口长度 i - j + 1。
# 时间复杂度：O(n)，左右指针各自只向右移动；空间复杂度：O(1)，计数器最多保存 26 个字母。
class Solution:  # LeetCode 约定的题解类
    def numberOfSpecialSubstrings(self, s: str) -> int:  # s：由小写字母组成的字符串
        cnt = Counter()  # 记录窗口内每个字符出现的次数
        ans = j = 0  # ans 累计答案，j 是窗口左端（右端 i 由下面的循环给出）
        for i, c in enumerate(s):  # 同时取得窗口右端下标 i 与字符 c
            cnt[c] += 1  # 当前字符进入窗口，计数加一
            while cnt[c] > 1:  # 当前字符出现重复，收缩窗口
                cnt[s[j]] -= 1  # 左端字符移出窗口
                j += 1  # 左端指针右移
            ans += i - j + 1  # 以 i 结尾的合法子串个数正好等于当前窗口长度
        return ans  # 返回没有重复字符的子串总数
