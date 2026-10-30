# 题目：3329. 字符至少出现 K 次的子字符串 II（Count Substrings With K-Frequency Characters II）
# 思路：与 I 相同的滑动窗口计数；Python 的 int 不会溢出，因此无需像 C++ 那样改用 long long。
# 时间复杂度：O(n)，每个字符最多进出窗口各一次；空间复杂度：O(1)，计数器里最多 26 个字母。
class Solution:  # LeetCode 约定的题解类
    def numberOfSubstrings(self, s: str, k: int) -> int:  # s 为只含小写字母的字符串，k 是要求的最低出现次数
        cnt = Counter()  # 窗口内各字符的计数；Python 整数不会溢出，答案很大也没问题
        ans = l = 0  # ans 为答案，l 为窗口左边界，同时从 0 开始
        for c in s:  # 逐个字符作为窗口右端入窗
            cnt[c] += 1  # 入窗，计数加一
            while cnt[c] >= k:  # c 已达 k 次，窗口不合法，收缩左端
                cnt[s[l]] -= 1  # 左端字符出窗
                l += 1  # 左边界右移
            ans += l  # 起点在 [0, l-1] 的子串都合法，累加 l 个
        return ans  # 返回合法子串总数
