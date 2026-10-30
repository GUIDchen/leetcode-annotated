# 题目：471. 编码最短长度的字符串（Encode String with Shortest Length）
# 思路：区间 DP。f[i][j] 存 s[i..j] 的最短编码；先用「t+t 中找 t」得到最小周期把整段折叠成 k[子串]，再枚举切分点比较长度取更短者。
# 时间复杂度：O(n^4)，区间 O(n^2) × 切分 O(n) × 子串查找 O(n)；空间复杂度：O(n^2)，存所有区间的字符串结果。
class Solution:  # LeetCode 约定的题解类
    def encode(self, s: str) -> str:  # s 是待编码的原始字符串，返回它的最短压缩表示
        def g(i: int, j: int) -> str:  # 内部函数：尝试把整段 s[i..j] 折叠成「次数[子串]」的形式
            t = s[i : j + 1]  # 取出当前区间的原始子串
            if len(t) < 5:  # 折叠后最短形态是 a[b]，至少 4 个字符，长度不足 5 时折叠不会变短
                return t  # 直接返回原文，省掉无效尝试
            k = (t + t).index(t, 1)  # 在 t+t 中从下标 1 开始找 t，得到的 k 就是最小周期长度
            if k < len(t):  # k 小于长度说明 t 由若干等长块重复拼成，可以折叠
                cnt = len(t) // k  # 重复次数 = 总长度 // 最小周期长度
                return f"{cnt}[{f[i][i + k - 1]}]"  # 次数 + 方括号，方括号里放「一个周期的最短编码」，可继续折叠
            return t  # 无法折叠，只能返回原文

        n = len(s)  # 字符串长度，作为 DP 的规模
        f = [[None] * n for _ in range(n)]  # 二维表：f[i][j] 记录子串 s[i..j] 的最短编码
        for i in range(n - 1, -1, -1):  # 左端点从右往左枚举，保证依赖的更短区间已经算好
            for j in range(i, n):  # 右端点从左往右枚举，区间长度由短到长
                f[i][j] = g(i, j)  # 方案一：整段折叠（或原样返回）
                if j - i + 1 > 4:  # 长度不超过 4 时切分不可能更短，直接跳过
                    for k in range(i, j):  # 枚举切分点，把区间拆成 [i,k] 与 [k+1,j]
                        t = f[i][k] + f[k + 1][j]  # 方案二：两段各自的最短编码直接拼接
                        if len(f[i][j]) > len(t):  # 拼接结果更短才更新答案
                            f[i][j] = t  # 记录更优的编码
        return f[0][-1]  # 整个字符串的最短编码
