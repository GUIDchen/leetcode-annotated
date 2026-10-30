# 题目：3335. 字符串转换后的长度 I（Total Characters in String After Transformations I）
# 思路：用 f[i][j] 表示经过 i 轮变换后字母 j 的个数；每轮中 'z' 分裂成 "ab"，其余字母平移到下一个字母，逐轮递推后求和。
# 时间复杂度：O(26·t + |s|)；空间复杂度：O(26·t)。
class Solution:  # LeetCode 约定的题解类
    def lengthAfterTransformations(self, s: str, t: int) -> int:  # s 是初始字符串，t 是变换轮数
        f = [[0] * 26 for _ in range(t + 1)]  # f[i][j] 表示 i 轮变换后字母 j 的出现次数
        for c in s:  # 统计初始串中每个字母的个数
            f[0][ord(c) - ord("a")] += 1  # ord(c) - ord("a") 把字母映射到 0..25
        for i in range(1, t + 1):  # 逐轮递推
            f[i][0] = f[i - 1][25]  # 上一轮的 'z' 变成 "ab"，为 a 贡献一个字符
            f[i][1] = f[i - 1][0] + f[i - 1][25]  # 上一轮的 'a' 平移到 b，'z' 分裂也多出一个 b
            for j in range(2, 26):  # 其余字母由前一个字母平移而来
                f[i][j] = f[i - 1][j - 1]  # 字母 j 的数量继承自上一轮的 j-1
        mod = 10**9 + 7  # 取模常量
        return sum(f[t]) % mod  # 26 个字母的数量之和即为答案
