# 题目：1830. 使字符串有序的最少操作次数（Minimum Number of Operations to Make String Sorted）
# 思路：答案等于当前排列的字典序名次；逐位统计更小字母提供的排列数，并乘各字母重复次数的阶乘逆元去重。
# 时间复杂度：O(n^2 + N)，n 为串长、N 为预处理上界；空间复杂度：O(N)，两个阶乘/逆元数组。
n = 3010  # 预处理上界：题目串长不超过 3000
mod = 10**9 + 7  # 取模常量
f = [1] + [0] * n  # f[i] = i! mod mod
g = [1] + [0] * n  # g[i] = i! 的模逆元

for i in range(1, n):  # 预处理阶乘与逆元
    f[i] = f[i - 1] * i % mod  # 递推求阶乘
    g[i] = pow(f[i], mod - 2, mod)  # 内置 pow 的三参数形式直接求模逆元


class Solution:  # LeetCode 约定的题解类
    def makeStringSorted(self, s: str) -> int:  # s：输入字符串；返回把它变成有序字符串所需的最少操作次数
        cnt = Counter(s)  # 统计每个字符出现的次数
        ans, n = 0, len(s)  # ans 累计答案；n 是字符串长度（同时覆盖同名的全局变量）
        for i, c in enumerate(s):  # 逐位统计名次贡献
            m = sum(v for a, v in cnt.items() if a < c)  # 剩余字符中比 c 小的字母总数
            t = f[n - i - 1] * m  # 剩余位置的全排列数乘以更小字母的可选个数
            for v in cnt.values():  # 除以各字母重复次数的阶乘（乘逆元实现）
                t = t * g[v] % mod  # 乘以 g[v] 并取模
            ans = (ans + t) % mod  # 累加并取模
            cnt[c] -= 1  # 当前字母用掉一个
            if cnt[c] == 0:  # 该字母已经用完
                cnt.pop(c)  # 从计数器中删除，避免继续参与去重计算
        return ans  # 返回最少操作次数
