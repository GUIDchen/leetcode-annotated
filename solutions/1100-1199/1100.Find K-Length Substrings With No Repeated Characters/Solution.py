# 题目：1100. 长度为 K 的无重复字符子串（Find K-Length Substrings With No Repeated Characters）
# 思路：用 Counter 维护长度为 k 的滑动窗口，len(cnt) == k 说明窗口内字符各不相同。
# 时间复杂度：O(n)，每个字符进出窗口各一次；空间复杂度：O(k)，计数表最多 k 个不同字符。
class Solution:  # LeetCode 约定的题解类
    def numKLenSubstrNoRepeats(self, s: str, k: int) -> int:  # s 是源字符串，k 是目标子串长度
        cnt = Counter(s[:k])  # 统计第一个长度为 k 的窗口
        ans = int(len(cnt) == k)  # 不同字符数等于 k 就无重复，bool 转 int 作为初始答案
        for i in range(k, len(s)):  # 窗口右端从 k 开始滑动
            cnt[s[i]] += 1  # 新字符进入窗口
            cnt[s[i - k]] -= 1  # 最左侧字符离开窗口
            if cnt[s[i - k]] == 0:  # 出现次数归零的键要删掉
                cnt.pop(s[i - k])  # 否则 len(cnt) 会比真实的不同字符数偏大
            ans += int(len(cnt) == k)  # 每个窗口判一次，无重复就累加 1
        return ans  # 返回满足条件的子串个数
