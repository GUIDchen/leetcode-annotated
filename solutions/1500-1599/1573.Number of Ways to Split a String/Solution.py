# 题目：1573. 分割字符串的方案数（Number of Ways to Split a String）
# 思路：设 '1' 的总数为 cnt。cnt 不能被 3 整除则无解；cnt 为 0 时是选两个切点的组合数 C(n-1, 2)；
#       否则每段各含 cnt/3 个 '1'，答案 = 第一刀可选空档数 × 第二刀可选空档数。
# 时间复杂度：O(n)，几次线性扫描；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def numWays(self, s: str) -> int:  # s：只含 '0' 与 '1' 的字符串
        def find(x):  # 找到第 x 个 '1' 所在的下标
            t = 0  # 已遇到的 '1' 的个数
            for i, c in enumerate(s):  # 同时取得下标 i 与字符 c
                t += int(c == '1')  # 遇到 '1' 就把计数加一
                if t == x:  # 正好数到第 x 个 '1'
                    return i  # 返回它的下标

        cnt, m = divmod(sum(c == '1' for c in s), 3)  # 一次性得到 '1' 的个数除以 3 的商与余数
        if m:  # 余数非零说明 '1' 的个数不能被 3 整除
            return 0  # 无法均分，方案数为 0
        n = len(s)  # 字符串长度
        mod = 10**9 + 7  # 结果对 1e9+7 取模
        if cnt == 0:  # 特例：整个字符串没有 '1'
            return ((n - 1) * (n - 2) // 2) % mod  # 从 n-1 个空隙里选两个切点，即 C(n-1, 2)
        i1, i2 = find(cnt), find(cnt + 1)  # 第一段末尾 '1' 与第二段开头 '1' 的位置，决定第一刀的可选空档
        j1, j2 = find(cnt * 2), find(cnt * 2 + 1)  # 第二段末尾 '1' 与第三段开头 '1' 的位置，决定第二刀的可选空档
        return (i2 - i1) * (j2 - j1) % (10**9 + 7)  # 两刀的选择数相乘后取模
