# 题目：2851. 字符串转换（String Transformation）
# 核心思路：k 次右移等价于「旋转量」在 0 与非 0 之间跳转，用 Z 算法找出 t 对应的旋转量，再用矩阵快速幂求 k 步的方案数。
# 时间复杂度：O(n + log k)；空间复杂度：O(n)。
# 说明：下面这段三引号字符串是原作者的英文思路笔记，属于代码的一部分（字符串字面量），因此整体保持原样，不做任何改动。
"""
DP, Z-algorithm, Fast mod.
Approach
How to represent a string?
Each operation is just a rotation. Each result string can be represented by an integer from 0 to n - 1. Namely, it's just the new index of s[0].
How to find the integer(s) that can represent string t?
Create a new string s + t + t (length = 3 * n).
Use Z-algorithm (or KMP), for each n <= index < 2 * n, calculate the maximum prefix length that each substring starts from index can match, if the length >= n, then (index - n) is a valid integer representation.
How to get the result?
It's a very obvious DP.
If we use an integer to represent a string, we only need to consider the transition from zero to non-zero and from non-zero to zero. In other words, all the non-zero strings should have the same result.
So let dp[t][i = 0/1] be the number of ways to get the zero/nonzero string
after excatly t steps.
Then
dp[t][0] = dp[t - 1][1] * (n - 1).
All the non zero strings can make it.
dp[t][1] = dp[t - 1][0] + dp[t - 1] * (n - 2).
For a particular non zero string, all the other non zero strings and zero string can make it.
We have dp[0][0] = 1 and dp[0][1] = 0
Use matrix multiplication.
How to calculate dp[k][x = 0, 1] faster?
Use matrix multiplication
vector (dp[t - 1][0], dp[t - 1][1])
multiplies matrix
[0 1]
[n - 1 n - 2]
== vector (dp[t][0], dp[t - 1][1]).
So we just need to calculate the kth power of the matrix which can be done by fast power algorith.
Complexity
Time complexity:
O(n + logk)
Space complexity:
O(n)
"""


class Solution:  # LeetCode 约定的题解类
    M: int = 1000000007  # 取模常量，通过 self.M 访问

    def add(self, x: int, y: int) -> int:  # 模意义下的加法
        x += y  # 先把 y 累加到 x 上
        if x >= self.M:  # 达到模数就减去一次模数
            x -= self.M
        return x  # 返回模意义下的和

    def mul(self, x: int, y: int) -> int:  # 模意义下的乘法
        return int(x * y % self.M)  # Python 整数不会溢出，先乘再取模即可

    def getZ(self, s: str) -> List[int]:  # Z 算法：z[i] 为 s[i..] 与 s 本身的最长公共前缀长度
        n = len(s)  # 串长
        z = [0] * n  # z 数组初始化为 0
        left = right = 0  # 当前最靠右的已匹配区间端点
        for i in range(1, n):  # i 从 1 开始扫描
            if i <= right and z[i - left] <= right - i:  # 落在已知区间内且可直接继承
                z[i] = z[i - left]  # 复制对称位置的答案
            else:  # 否则逐个字符向外扩展
                z_i = max(0, right - i + 1)  # 从区间右端外一格起步
                while i + z_i < n and s[i + z_i] == s[z_i]:  # 字符相同就继续向右延伸
                    z_i += 1  # 匹配长度加一
                z[i] = z_i  # 记录该位置的结果
            if i + z[i] - 1 > right:  # 若右端超过已知最右端就更新区间
                left = i  # 新区间左端
                right = i + z[i] - 1  # 新区间右端
        return z  # 返回 z 数组

    def matrixMultiply(self, a: List[List[int]], b: List[List[int]]) -> List[List[int]]:  # 矩阵乘法：a 是 m x n，b 是 n x p
        m = len(a)  # a 的行数
        n = len(a[0])  # 公共维度 n
        p = len(b[0])  # b 的列数
        r = [[0] * p for _ in range(m)]  # 结果矩阵 m x p，初值为 0
        for i in range(m):  # 枚举行
            for j in range(p):  # 枚举列
                for k in range(n):  # 枚举累加维度
                    r[i][j] = self.add(r[i][j], self.mul(a[i][k], b[k][j]))  # 每一项在模意义下累加
        return r  # 返回结果矩阵

    def matrixPower(self, a: List[List[int]], y: int) -> List[List[int]]:  # 矩阵快速幂：求 a 的 y 次方
        n = len(a)  # 方阵阶数
        r = [[0] * n for _ in range(n)]  # 结果先构造成零矩阵
        for i in range(n):  # 主对角线置 1，即单位矩阵
            r[i][i] = 1  # 单位矩阵对角线
        x = [a[i][:] for i in range(n)]  # 深拷贝底数，避免改动入参
        while y > 0:  # 二进制拆分指数
            if y & 1:  # 当前位为 1 时乘入
                r = self.matrixMultiply(r, x)  # 累乘到结果
            x = self.matrixMultiply(x, x)  # 底数平方，对应指数翻倍
            y >>= 1  # 指数右移一位
        return r  # 返回幂矩阵

    def numberOfWays(self, s: str, t: str, k: int) -> int:  # 主函数：统计 k 次右移后 s 变成 t 的方案数
        n = len(s)  # 字符串长度
        dp = self.matrixPower([[0, 1], [n - 1, n - 2]], k)[0]  # 转移矩阵的 k 次幂第一行即 dp[k][0] 与 dp[k][1]
        s += t + t  # 一次追加即可拼出 s + t + t 中的 s + t
        z = self.getZ(s)  # 对拼接后的串求 z 数组
        m = n + n  # 只检查偏移 n .. 2n-1
        result = 0  # 累计方案数
        for i in range(n, m):  # 枚举 t 的每个起点
            if z[i] >= n:  # 前缀匹配长度达到 n，说明该偏移是合法的旋转量
                result = self.add(result, dp[0] if i - n == 0 else dp[1])  # 偏移 0 用 dp[0]，非零偏移共用 dp[1]
        return result  # 返回总方案数
