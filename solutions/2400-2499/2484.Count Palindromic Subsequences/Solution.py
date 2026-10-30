# 题目：2484. 统计回文子序列数目（Count Palindromic Subsequences）
# 思路：回文子序列必为 a b c b a；枚举中心位置，用前后缀计数表相乘拼出所有形如 (j,k,c,k,j) 的方案。
# 时间复杂度：O(n * 10 * 10)，n 为串长；空间复杂度：O(n * 10 * 10)，即 pre、suf 两张计数表。
class Solution:  # LeetCode 约定的题解类
    def countPalindromes(self, s: str) -> int:  # s：只含数字字符的字符串；返回长度为 5 的回文子序列个数
        mod = 10**9 + 7  # 取模常量：答案很大，按题意对 1e9+7 取模
        n = len(s)  # 字符串长度
        pre = [[[0] * 10 for _ in range(10)] for _ in range(n + 2)]  # pre[i][j][k]：前缀 s[:i] 中形如「j 在前、k 在后」的下标对个数
        suf = [[[0] * 10 for _ in range(10)] for _ in range(n + 2)]  # suf[i][j][k]：后缀 s[i-1:] 中形如「j 在前、k 在后」的下标对个数
        t = list(map(int, s))  # 把字符预先转成数字，后面可直接当下标用
        c = [0] * 10  # c[d]：当前已扫描部分中数字 d 出现的次数
        for i, v in enumerate(t, 1):  # 从 1 开始编号，i 表示把前 i 个字符纳入统计
            for j in range(10):  # 枚举下标对的第一个数字 j
                for k in range(10):  # 枚举下标对的第二个数字 k
                    pre[i][j][k] = pre[i - 1][j][k]  # 先整体继承前一个前缀的计数
            for j in range(10):  # 用新字符 v 作为下标对的第二个元素去扩展
                pre[i][j][v] += c[j]  # v 之前 j 出现过 c[j] 次，故新增 c[j] 个 (j, v) 下标对
            c[v] += 1  # v 计入已扫描次数，供后续位置使用
        c = [0] * 10  # 计数清空，复用同一个数组做从右往左的扫描
        for i in range(n, 0, -1):  # 从后往前构造后缀表，i 表示把 s[i-1:] 纳入统计
            v = t[i - 1]  # 本次新纳入的数字
            for j in range(10):  # 枚举下标对的第一个数字 j
                for k in range(10):  # 枚举下标对的第二个数字 k
                    suf[i][j][k] = suf[i + 1][j][k]  # 继承右邻后缀的计数
            for j in range(10):  # 用新字符 v 作为下标对的首元素向左扩展
                suf[i][j][v] += c[j]  # v 在左、j 在右的组合新增 c[j] 个
            c[v] += 1  # v 计入已扫描次数
        ans = 0  # 答案累加器
        for i in range(1, n + 1):  # 枚举回文子序列的中心位置（长度为 5，中心是唯一的中位字符）
            for j in range(10):  # 枚举前半部分第一个数字 j
                for k in range(10):  # 枚举前半部分第二个数字 k
                    ans += pre[i - 1][j][k] * suf[i + 1][j][k]  # 左右两侧 (j, k) 下标对数量相乘，即所有 j k c k j 方案的组合数
                    ans %= mod  # 随时取模，防止数值膨胀
        return ans  # 返回方案总数
