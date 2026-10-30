# 题目：2911. 得到 K 个半回文串的最少修改次数（Minimum Changes to Make K Semi-palindromes）
# 核心思路：预处理 g[i][j]＝把 s[i-1..j-1] 变成半回文串的最少修改次数（枚举长度因子 d 当周期，按同余类配对统计差异），再做「前 i 个字符切成 j 段」的区间 DP。
# 时间复杂度：O(n^2 * d + k*n^2)，d 为因子个数；空间复杂度：O(n^2 + n*k)。
class Solution:  # LeetCode 约定的题解类
    def minimumChanges(self, s: str, k: int) -> int:  # s 是待拆分字符串，k 是段数，返回最少修改次数
        n = len(s)  # 字符串长度
        g = [[inf] * (n + 1) for _ in range(n + 1)]  # g[i][j]：把 s[i-1..j-1] 变成半回文串的最少修改次数，先全部设为 inf
        for i in range(1, n + 1):  # 枚举子串左端点（1 基）
            for j in range(i, n + 1):  # 枚举子串右端点，子串为 s[i-1..j-1]
                m = j - i + 1  # 子串长度 m
                for d in range(1, m):  # 枚举周期 d，它必须整除长度 m
                    if m % d == 0:  # 只有整除时才能按 d 个交错回文序列拆分
                        cnt = 0  # 当前周期下需要修改的字符对数
                        for l in range(m):  # 枚举子串内位置 l
                            r = (m // d - 1 - l // d) * d + l % d  # 同余类 l%d 中从末尾数过来的对称位置
                            if l >= r:  # 越过中点，配对会重复，终止扫描
                                break  # 跳出配对循环
                            if s[i - 1 + l] != s[i - 1 + r]:  # 配对字符不同则要改一次
                                cnt += 1  # 修改次数加一
                        g[i][j] = min(g[i][j], cnt)  # 所有周期取最小，作为该子串变成半回文串的代价

        f = [[inf] * (k + 1) for _ in range(n + 1)]  # f[i][j]：前 i 个字符切成 j 段半回文串的最少修改次数，初始为 inf
        f[0][0] = 0  # 边界：前 0 个字符切 0 段，修改 0 次
        for i in range(1, n + 1):  # 枚举前缀长度 i
            for j in range(1, k + 1):  # 枚举已切段数 j
                for h in range(i - 1):  # 枚举最后一段起点 h；半回文串长度至少为 2，所以 h 最多到 i-2
                    f[i][j] = min(f[i][j], f[h][j - 1] + g[h + 1][i])  # 前 h 个字符切 j-1 段，再拼上最后一段 s[h..i-1] 的代价
        return f[n][k]  # 答案：前 n 个字符切成 k 段的最小修改次数
