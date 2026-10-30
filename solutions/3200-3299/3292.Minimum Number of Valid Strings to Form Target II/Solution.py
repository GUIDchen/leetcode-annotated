# 题目：3292. 形成目标字符串需要的最少字符串数 II（Minimum Number of Valid Strings to Form Target II）
# 思路：Rolling Hash 预处理 target，按长度分桶存候选串前缀哈希，二分出每个位置的最长可匹配长度，再用贪心区间覆盖求最少串数。
# 时间复杂度：O((n + L) + n·log m)；空间复杂度：O(n + L)，用于哈希表、幂数组与分桶集合。
class Hashing:  # 字符串哈希工具：O(1) 求任意子串哈希
    __slots__ = ["mod", "h", "p"]  # 限制实例属性，既省内存又避免写错属性名

    def __init__(self, s: List[str], base: int, mod: int):  # 构造函数：s 是待哈希的串
        self.mod = mod  # 保存模数，query 里要用
        self.h = [0] * (len(s) + 1)  # 前缀哈希数组，长度 len(s)+1
        self.p = [1] * (len(s) + 1)  # 幂数组，p[0]=1，其余由递推得到
        for i in range(1, len(s) + 1):  # 递推计算幂与前缀哈希
            self.h[i] = (self.h[i - 1] * base + ord(s[i - 1])) % mod  # h[i] = h[i-1] * base + s[i-1]（用 ord 取字符编码）
            self.p[i] = (self.p[i - 1] * base) % mod  # p[i] = p[i-1] * base

    def query(self, l: int, r: int) -> int:  # 求子串 s[l-1..r) 的哈希（下标从 1 开始）
        return (self.h[r] - self.h[l - 1] * self.p[r - l + 1]) % self.mod  # 前缀哈希相减对齐，Python 取模天然非负


class Solution:  # LeetCode 约定的题解类
    def minValidStrings(self, words: List[str], target: str) -> int:  # words：候选串列表；target：目标串
        def f(i: int) -> int:  # 返回从 target[i] 开始最多能匹配的候选串前缀长度
            l, r = 0, min(n - i, m)  # 长度上界：不越界且不超过最长候选串
            while l < r:  # 二分查找最大的可行长度
                mid = (l + r + 1) >> 1  # 向上取整的中点
                sub = hashing.query(i + 1, i + mid)  # target[i..i+mid) 这段的哈希
                if sub in s[mid]:  # 该长度存在相同的前缀哈希，说明可以匹配
                    l = mid  # 可行，尝试更长
                else:  # 否则不可行
                    r = mid - 1  # 缩短上界
            return l  # 返回最大可匹配长度

        base, mod = 13331, 998244353  # 哈希的进制与模数
        hashing = Hashing(target, base, mod)  # 预处理 target 的哈希
        m = max(len(w) for w in words)  # 最长候选串长度
        s = [set() for _ in range(m + 1)]  # s[len] 存所有候选串中长度为 len 的前缀哈希
        for w in words:  # 遍历候选串，把所有前缀哈希按长度分桶
            h = 0  # 当前前缀哈希的累积值
            for j, c in enumerate(w, 1):  # j 从 1 开始，表示当前前缀的长度
                h = (h * base + ord(c)) % mod  # 滚动计算前缀哈希
                s[j].add(h)  # 记录长度为 j 的前缀哈希
        ans = last = mx = 0  # ans 记串数；last 是当前串覆盖到的右端；mx 是可达的最右端
        n = len(target)  # 目标串长度（f 通过闭包使用，必须在调用前定义）
        for i in range(n):  # 逐位置扫描 target
            dist = f(i)  # 从 i 起最多能匹配的长度
            mx = max(mx, i + dist)  # 更新可达的最右端
            if i == last:  # 走到当前覆盖边界，必须新开一个串
                if i == mx:  # 一个字符都匹配不了，永远拼不出 target
                    return -1  # 按题意返回 -1
                last = mx  # 新的一段覆盖到 mx
                ans += 1  # 串数加一
        return ans  # 返回最少串数
