# 题目：1316. 不同的循环子字符串（Distinct Echo Substrings）
# 思路：用字符串哈希判等，枚举每个偶数长度子串并比较前后两半的哈希值，哈希值放进集合去重。
# 时间复杂度：O(n^2)，枚举区间 O(n^2) 而比较是 O(1)；空间复杂度：O(n)，前缀哈希与幂次数组。
class Solution:  # LeetCode 约定的题解类
    def distinctEchoSubstrings(self, text: str) -> int:  # text 为输入字符串
        def get(l, r):  # 取字符串下标区间 [l, r]（1 起）的哈希值
            return (h[r] - h[l - 1] * p[r - l + 1]) % mod  # 前缀哈希相减并取模，得到该子串的哈希值

        n = len(text)  # 字符串长度 n
        base = 131  # 哈希基数 131，大于小写字母表大小
        mod = int(1e9) + 7  # 取模用的大素数，即 1e9 + 7
        h = [0] * (n + 10)  # h[i] 为 text 前 i 个字符的前缀哈希
        p = [1] * (n + 10)  # p[i] = base^i，用于拼接哈希时对齐幂次
        for i, c in enumerate(text):  # 逐字符递推前缀哈希与幂次
            t = ord(c) - ord('a') + 1  # 字符映射到 1..26，避免 0 造成前导零歧义
            h[i + 1] = (h[i] * base) % mod + t  # 滚动哈希：h[i+1] = h[i] * base + 当前字符值
            p[i + 1] = (p[i] * base) % mod  # 预计算幂次 base^(i+1)
        vis = set()  # 集合去重，记录出现过的「左半段」哈希值
        for i in range(n - 1):  # 枚举回声子串的起点 i
            for j in range(i + 1, n, 2):  # 枚举终点 j，步长 2 保证子串长度为偶数，才能均分成两半
                k = (i + j) >> 1  # 中点 k：左半段为 [i, k]，右半段为 [k+1, j]
                a = get(i + 1, k + 1)  # 左半段哈希（哈希下标从 1 开始，故区间为 [i+1, k+1]）
                b = get(k + 2, j + 1)  # 右半段哈希（区间为 [k+2, j+1]）
                if a == b:  # 两半哈希相同即为一回声子串
                    vis.add(a)  # 把哈希值放进集合去重
        return len(vis)  # 集合大小即不同回声子串的个数
