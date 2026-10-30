# 题目：3031. 将单词恢复初始状态所需的最短时间 II（Minimum Time to Revert Word to Initial State II）
# 思路：用滚动哈希代替逐字符比较，判断「剩余后缀 == 原串等长前缀」只需 O(1)，从 i = k 开始枚举删除的字符数。
# 时间复杂度：O(n)，预处理 O(n) 加至多 n/k 次 O(1) 查询；空间复杂度：O(n)，存幂次数组与前缀哈希数组。
class Hashing:  # 字符串哈希工具类：预处理幂次与前缀哈希，支持 O(1) 查询子串哈希
    __slots__ = ["mod", "h", "p"]  # 用 slots 固定属性名，减少每个实例的内存开销

    def __init__(self, s: str, base: int, mod: int):  # s：待预处理字符串；base：进制；mod：模数
        self.mod = mod  # 保存模数，query 里要用
        self.h = [0] * (len(s) + 1)  # h[i]：前缀 s[0..i-1] 的哈希值，多开一位方便 1 基下标
        self.p = [1] * (len(s) + 1)  # p[i]：base 的 i 次方对 mod 取模，初值 1 对应 0 次方
        for i in range(1, len(s) + 1):  # 递推预处理前缀哈希与幂次
            self.h[i] = (self.h[i - 1] * base + ord(s[i - 1])) % mod  # 前缀哈希递推，字符取 ASCII 码参与计算
            self.p[i] = (self.p[i - 1] * base) % mod  # 幂次递推：base^i = base^(i-1) * base

    def query(self, l: int, r: int) -> int:  # 求 1 基下标区间 [l, r] 的子串哈希
        return (self.h[r] - self.h[l - 1] * self.p[r - l + 1]) % self.mod  # 差分取模，Python 取模结果自动非负


class Solution:  # LeetCode 约定的题解类
    def minimumTimeToInitialState(self, word: str, k: int) -> int:  # word：初始单词；k：每秒删除的字符数
        hashing = Hashing(word, 13331, 998244353)  # 用固定进制与模数预处理整串哈希
        n = len(word)  # 单词长度
        for i in range(k, n, k):  # i 是已删除的字符数，按 k 的整数倍递增
            if hashing.query(1, n - i) == hashing.query(i + 1, n):  # 原串前缀与剩余后缀的哈希相同
                return i // k  # 说明此时补字符即可复原，耗时 i // k 秒
        return (n + k - 1) // k  # 单词删空后仍需补满一段字符，向上取整得到总秒数
