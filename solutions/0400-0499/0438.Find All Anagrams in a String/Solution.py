# 题目：438. 找到字符串中所有字母异位词（Find All Anagrams in a String）
# 思路：固定长度滑动窗口 + Counter 计数——窗口右移时加入 s[i]、移出 s[i-n+1]，两个 Counter 相等即说明该窗口是 p 的异位词。
# 时间复杂度：O(m * 26)，m 为主串长度，Counter 比较的规模是字母表大小；空间复杂度：O(1)，只存 26 个字母的计数。
class Solution:  # LeetCode 约定的题解类
    def findAnagrams(self, s: str, p: str) -> List[int]:  # 返回 s 中所有 p 的字母异位词子串的起始下标
        m, n = len(s), len(p)  # m 为主串长度，n 为模式串长度（也就是滑动窗口的大小）
        ans = []  # 答案列表，按从左到右的顺序记录起始下标
        if m < n:  # 主串比模式串还短，不可能存在异位词
            return ans  # 提前返回空答案
        cnt1 = Counter(p)  # cnt1：p 的字母计数表
        cnt2 = Counter(s[: n - 1])  # cnt2：先放入窗口的前 n-1 个字符，后面每轮再补上第 n 个形成长度 n 的窗口
        for i in range(n - 1, m):  # 窗口右端点从 n-1 滑到 m-1，i 即窗口的右端下标
            cnt2[s[i]] += 1  # 右端纳入新字符，窗口长度变为 n
            if cnt1 == cnt2:  # 两个 Counter 相等，说明窗口内字符组成与 p 相同
                ans.append(i - n + 1)  # 窗口左端点 i - n + 1 就是一个答案，记录下标
            cnt2[s[i - n + 1]] -= 1  # 左端最左侧字符移出窗口，为下一轮滑动做准备
        return ans  # 返回收集到的全部起始下标
