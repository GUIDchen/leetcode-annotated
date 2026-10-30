# 题目：1638. 统计只差一个字符的子串数目（Count Substrings That Differ by One Character）
# 思路：枚举 s、t 中「恰好不同的那一对位置」，向左右扩展相同字符，得到以该位置为唯一差异点的子串数 (l+1)(r+1)。
# 时间复杂度：O(m·n·(m+n))，每个位置对最坏向两侧扩展；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countSubstrings(self, s: str, t: str) -> int:  # s、t 是两个字符串，返回只差一个字符的子串对数
        ans = 0  # 累计答案
        m, n = len(s), len(t)  # m、n 分别是 s、t 的长度
        for i, a in enumerate(s):  # 枚举 s 中作为「差异位置」的下标 i 与字符 a
            for j, b in enumerate(t):  # 枚举 t 中作为「差异位置」的下标 j 与字符 b
                if a != b:  # 只有字符不同时，这一对位置才能当唯一的差异点
                    l = r = 0  # l 记录向左能延伸的相同字符个数，r 记录向右能延伸的个数
                    while i > l and j > l and s[i - l - 1] == t[j - l - 1]:  # 向左侧扩展：越界或字符不同就停止
                        l += 1  # 左侧又多匹配一个字符
                    while (  # 向右侧扩展（条件较长所以用括号换行）
                        i + r + 1 < m and j + r + 1 < n and s[i + r + 1] == t[j + r + 1]  # 续行：两个下标都还在范围内且字符相同才继续
                    ):  # while 条件结束
                        r += 1  # 右侧又多匹配一个字符
                    ans += (l + 1) * (r + 1)  # 差异点左侧可选 l+1 种起点、右侧可选 r+1 种终点，共 (l+1)(r+1) 个合法子串
        return ans  # 返回统计结果
