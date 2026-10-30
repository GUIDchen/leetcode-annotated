# 题目：1915. 最美子字符串的数目（Number of Wonderful Substrings）
# 思路：前缀奇偶性状态压缩。用 10 位掩码表示各字母出现次数的奇偶性，字典 cnt 统计每个掩码作为前缀出现的次数；相同掩码配对得全偶数子串，只差一位配对得恰一个字母奇数次。
# 时间复杂度：O(10n)，每个字符枚举 10 种掩码；空间复杂度：O(2^10) = O(1)。
class Solution:  # LeetCode 约定的题解类
    def wonderfulSubstrings(self, word: str) -> int:  # word 只含 'a'~'j'，返回其中最美子字符串的个数
        cnt = defaultdict(int)  # 默认字典充当哈希表：键是前缀掩码，值是它出现的次数，缺失键自动按 0 计数
        cnt[0] = 1  # 空前缀的掩码是 0，先记 1 次，用于表示“从开头到当前位置”这类子串
        ans = st = 0  # ans 累加答案，st 是当前前缀的掩码（第 i 位为 1 表示字母 i 出现奇数次）
        for c in word:  # 从左到右逐个字符扩展前缀
            st ^= 1 << (ord(c) - ord("a"))  # 用异或翻转对应位：ord 差值把字母映射到 0~9
            ans += cnt[st]  # 之前有相同掩码的前缀 ⇒ 两前缀之间所有字母都是偶数次
            ans += sum(cnt[st ^ (1 << i)] for i in range(10))  # 只差一位掩码的两前缀之间恰有一个字母奇数次，枚举 10 种可能并求和
            cnt[st] += 1  # 当前前缀掩码的计数 +1，供后续前缀配对
        return ans  # 返回最美子字符串总数
