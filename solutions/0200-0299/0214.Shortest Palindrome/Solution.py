# 题目：214. 最短回文串（Shortest Palindrome）
# 核心思路：滚动哈希同时算前缀的正向哈希与反向哈希，定位最长的回文前缀；把剩余后缀反转后拼到原串前面即为答案。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，切片与反转产生额外字符串。
class Solution:  # LeetCode 约定的题解类
    def shortestPalindrome(self, s: str) -> str:  # 在 s 前面补最少字符使其成为回文，返回该最短回文串
        base = 131  # 滚动哈希的进制，取大于 26 的质数以降低碰撞概率
        mod = 10**9 + 7  # 取模，避免哈希值随串长无限变大
        n = len(s)  # 串长
        prefix = suffix = 0  # prefix：前缀的正向哈希；suffix：前缀的反向哈希
        mul = 1  # 当前位的权重 base^i
        idx = 0  # 最长的回文前缀长度
        for i, c in enumerate(s):  # 同时取得下标 i 和字符 c，逐位扩展前缀
            prefix = (prefix * base + (ord(c) - ord('a') + 1)) % mod  # 正向哈希：整体左移一位后接当前字符，字符映射到 1..26
            suffix = (suffix + (ord(c) - ord('a') + 1) * mul) % mod  # 反向哈希：当前字符乘权重后追加到右端
            mul = (mul * base) % mod  # 权重翻倍，供下一位使用
            if prefix == suffix:  # 两种哈希相等说明 s[0..i] 是回文
                idx = i + 1  # 记录这个回文前缀的长度
        return s if idx == n else s[idx:][::-1] + s  # 整串已是回文就直接返回，否则把剩余部分反转后拼到前面
