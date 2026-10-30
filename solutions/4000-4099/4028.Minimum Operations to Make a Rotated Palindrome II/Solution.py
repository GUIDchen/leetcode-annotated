# 4028. 得到旋转回文字符串的最少操作次数 II / Minimum Operations to Make a Rotated Palindrome II
# 核心思路：先把字母修改代价按 26 次单位根展开成频率求和，再用 FFT 做循环相关，一次性求出每个旋转位置作为回文中心时的最小修改代价，最后叠加旋转次数 k 取最小值。
# 复杂度：时间 O(14 · M log M + 26^2)，空间 O(M)（M 为不小于 2n 的 2 的幂）。
import numpy as np  # 引入 numpy，用于 FFT 与向量化运算


class Solution:  # 题解类定义
    def minOperations(self, s: str) -> int:  # 返回把 s 旋转后变成回文串所需的最少操作次数（旋转 + 修改字母）
        n = len(s)  # 字符串长度

        size = 1  # FFT 长度，取不小于 2n 的最小 2 的幂
        while size < 2 * n:  # 不断翻倍，直到长度足够
            size <<= 1  # 长度翻倍

        nums = np.array([ord(c) - ord('a') for c in s], dtype=np.int64)  # 把每个字符映射成 0..25 的整数数组

        cost = np.zeros(26)  # cost[t] 是代价函数按 26 次单位根展开后的第 t 个频率系数

        for t in range(26):  # 枚举频率 t（0..25）
            for z in range(26):  # 枚举字母间的环形距离 z（0..25）
                cost[t] += min(z, 26 - z) * math.cos(2 * math.pi * t * z / 26)  # 字母相差 z 个位置时的最小修改代价做离散傅里叶变换

        dp = np.zeros(n)  # dp[c] 记录配对中心落在 c 时的累计修改代价

        for t in range(14):  # 只需枚举 0..13 共 14 个频率，另一半由共轭对称性得到
            theta = 2 * math.pi * t / 26  # 第 t 个频率对应的角度

            a = np.exp(1j * theta * nums)  # 把每个字符映射到单位圆上的 e^{i·theta·num}
            a = np.pad(a, (0, size - n))  # 右侧补零到 FFT 长度，避免循环卷积混叠

            b = np.conj(a)  # 取共轭，用于构造相关运算

            fa = np.fft.fft(a)  # 输入序列的正变换
            fb = np.fft.fft(b)  # 共轭序列的正变换

            conv = np.fft.ifft(fa * fb).real  # 频域相乘后做逆变换，取实部得到相关结果

            mult = 1 if t == 0 or t == 13 else 2  # t = 0 与 t = 13 是实轴上的双重频率，只算一次

            dp += mult * cost[t] * (conv[:n] + conv[n : 2 * n])  # 把两段长度 n 的窗口相加，再乘以系数累加进 dp

        ans = inf  # 答案初值为无穷大

        for k in range(n):  # 枚举旋转次数 k
            c = (2 * k + n - 1) % n  # 旋转 k 次后，配对中心在相关数组中的下标
            d = round(dp[c] / 52)  # 除以 52（26 个频率 × 2 段长度 n 的窗口）并四舍五入，还原真实修改代价

            ans = min(ans, k + d)  # 总操作次数 = 旋转次数 + 字母修改代价

        return ans  # 返回最少操作次数
