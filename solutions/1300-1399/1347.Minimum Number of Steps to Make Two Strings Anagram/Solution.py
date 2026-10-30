# 题目：1347. 制造字母异位词的最小步骤数（Minimum Number of Steps to Make Two Strings Anagram）
# 思路：先统计 s 的字符频次，再遍历 t 逐个扣减；某字符被扣成负数说明 s 中数量不够，必须替换 s 里的一个字符，步数加一。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(|Σ|) = O(1)，字母表只有 26 个字符。
class Solution:  # LeetCode 约定的题解类
    def minSteps(self, s: str, t: str) -> int:  # s 是待改造的字符串，t 是目标异位词
        cnt = Counter(s)  # Counter(s) 直接得到 s 的字符频次表
        ans = 0  # ans 统计需要替换的字符个数，也就是步数
        for c in t:  # 遍历 t 的每个字符，去消耗 s 的频次余量
            cnt[c] -= 1  # 该字符在 s 中的可用次数减一
            ans += cnt[c] < 0  # 扣成负数说明 s 里不够用，ans 加 1（bool 可直接参与加法）
        return ans  # 返回最小步数
