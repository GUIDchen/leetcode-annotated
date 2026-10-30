# 题目：3213. 最小代价构造字符串（Construct String with Minimum Cost）
# 思路：用字符串哈希把每个单词记成「哈希值 → 最小代价」，再令 f[i] 为拼出 target 前 i 个字符的最小代价，枚举出现过的单词长度并用哈希 O(1) 校验子串后转移。
# 时间复杂度：O(n · L)，n 为目标串长度、L 为不同单词长度个数；空间复杂度：O(n) 存前缀哈希与 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, target: str, words: List[str], costs: List[int]) -> int:  # target：目标串；words：可拼接的单词；costs：对应代价
        base, mod = 13331, 998244353  # 哈希进制与大质数模数
        n = len(target)  # 目标串长度
        h = [0] * (n + 1)  # h[i]：target 前 i 个字符的前缀哈希
        p = [1] * (n + 1)  # p[i]：base 的 i 次幂，用于区间哈希差分
        for i, c in enumerate(target, 1):  # 从 1 开始递推每一位的前缀哈希与幂
            h[i] = (h[i - 1] * base + ord(c)) % mod  # 前缀哈希递推：h[i] = h[i-1] * base + ord(c)
            p[i] = (p[i - 1] * base) % mod  # 幂递推：p[i] = base^i
        f = [0] + [inf] * n  # f[i]：拼出 target 前 i 个字符的最小代价，f[0] = 0，其余为无穷大
        ss = sorted(set(map(len, words)))  # 所有单词长度去重后升序排列，供枚举
        d = defaultdict(lambda: inf)  # 单词哈希值 → 最小代价，缺省值为无穷大
        min = lambda a, b: a if a < b else b  # 本地 min，避免反复查内置函数（此处覆盖内置 min）
        for w, c in zip(words, costs):  # 逐个单词计算哈希并登记最小代价
            x = 0  # 当前单词的哈希初值
            for ch in w:  # 逐字符滚动计算整个单词的哈希
                x = (x * base + ord(ch)) % mod  # 多项式哈希递推
            d[x] = min(d[x], c)  # 同一哈希重复出现时保留更小的代价
        for i in range(1, n + 1):  # 按前缀长度从小到大做 DP
            for j in ss:  # 枚举每一种可能的单词长度
                if j > i:  # 长度超过当前位置，更长的也放不下
                    break  # 因 ss 升序，直接跳出本层枚举
                x = (h[i] - h[i - j] * p[j]) % mod  # 取出子串 target[i-j:i] 的哈希值（Python 取模自动转为非负）
                f[i] = min(f[i], f[i - j] + d[x])  # 用 d[x] 的代价接在该段子串后面做转移
        return f[n] if f[n] < inf else -1  # 整个 target 无法拼出时返回 -1
