# 题目：467. 环绕字符串中唯一的子字符串（Unique Substrings in Wraparound String）
# 思路：环形串里以某字母结尾的子串，其最长可行长度 L 就代表 L 个不同的子串；统计每个字母结尾的最长环形递增段长度，求和即为答案。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数大小的哈希表。
class Solution:  # LeetCode 约定的题解类
    def findSubstringInWraproundString(self, s: str) -> int:  # s 为给定字符串
        f = defaultdict(int)  # f[c]：以字符 c 结尾的环形递增子串的最大长度
        k = 0  # k 表示当前连续环形递增段的长度
        for i, c in enumerate(s):  # 同时取得下标 i 与字符 c
            if i and (ord(c) - ord(s[i - 1])) % 26 == 1:  # 相邻字符在字母环上恰好相差 1（z 后接 a 也成立），i 为 0 时不算
                k += 1  # 递增段延长
            else:  # 否则说明递增段断了
                k = 1  # 重新从长度 1 开始
            f[c] = max(f[c], k)  # 更新以该字符结尾的最长长度
        return sum(f.values())  # 每个字母贡献其最长长度个唯一子串，求和即答案
