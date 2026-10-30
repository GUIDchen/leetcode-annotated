# 题目：3549. 两个多项式相乘（Multiply Two Polynomials）
# 思路：用 FFT 做卷积：补零到 2 的幂、两次正变换、频域点乘、一次逆变换，最后四舍五入还原整数系数。
# 时间复杂度：O(n log n)，n 为不小于结果长度的 2 的幂；空间复杂度：O(n)，两个长度为 n 的复数列表。
class Solution:  # LeetCode 约定的题解类
    def multiply(self, poly1: List[int], poly2: List[int]) -> List[int]:  # poly1 / poly2：多项式的系数，下标即次数
        if not poly1 or not poly2:  # 任一多项式为空
            return []  # 乘积就是空列表

        m = len(poly1) + len(poly2) - 1  # 乘积多项式的项数
        n = 1  # 补零后的长度，取不小于 m 的最小 2 的幂
        while n < m:  # 长度还不足以容纳全部结果系数
            n <<= 1  # 左移一位即乘以 2

        fa = list(map(complex, poly1)) + [0j] * (n - len(poly1))  # 第一个多项式转成复数列并补零到长度 n
        fb = list(map(complex, poly2)) + [0j] * (n - len(poly2))  # 第二个多项式转成复数列并补零到长度 n

        self._fft(fa, invert=False)  # 对第一个多项式做正变换
        self._fft(fb, invert=False)  # 对第二个多项式做正变换

        for i in range(n):  # 遍历频域上的每一个点
            fa[i] *= fb[i]  # 频域逐点相乘，等价于系数域的卷积

        self._fft(fa, invert=True)  # 逆变换回到系数域
        return [int(round(fa[i].real)) for i in range(m)]  # 取实部四舍五入，得到前 m 个有效系数

    def _fft(self, a: List[complex], invert: bool) -> None:  # 原地快速傅里叶变换；invert 为真时做逆变换
        n = len(a)  # 当前序列长度，必须是 2 的幂

        j = 0  # 位反转置换用的下标
        for i in range(1, n):  # 第一步：按下标的二进制位反转后重排
            bit = n >> 1  # 从最高位开始试探
            while j & bit:  # 当前位为 1，需要进位
                j ^= bit  # 清掉这一位
                bit >>= 1  # 继续试探下一位
            j ^= bit  # 置上找到的这一位，得到与 i 位反转对应的下标 j
            if i < j:  # 只在 i < j 时交换，避免把两个元素换回原位
                a[i], a[j] = a[j], a[i]  # 交换这两个元素

        len_ = 2  # 块长从 2 开始，逐层翻倍
        while len_ <= n:  # 依次合并长度为 2, 4, 8, ... 的块
            ang = 2 * math.pi / len_ * (-1 if invert else 1)  # 本层单位根的角度，逆变换取共轭方向
            wlen = complex(math.cos(ang), math.sin(ang))  # 本层的单位根 wlen = e^{i * ang}
            for i in range(0, n, len_):  # 枚举每一块
                w = 1 + 0j  # 旋转因子从 1 开始
                half = i + len_ // 2  # 块内后半部分的起点
                for j in range(i, half):  # 枚举块内的前半部分
                    u = a[j]  # 前半部分对应的元素
                    v = a[j + len_ // 2] * w  # 后半部分对应的元素乘上旋转因子
                    a[j] = u + v  # 蝶形运算：和写回前半部分
                    a[j + len_ // 2] = u - v  # 蝶形运算：差写回后半部分
                    w *= wlen  # 旋转因子推进到下一个单位根
            len_ <<= 1  # 块长翻倍

        if invert:  # 逆变换在最后还需要额外除以长度 n
            for i in range(n):  # 逐项归一化
                a[i] /= n  # 除以 n 完成逆变换
