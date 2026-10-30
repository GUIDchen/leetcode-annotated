// 题目：3549. 两个多项式相乘（Multiply Two Polynomials）
// 思路：把系数看作多项式系数后做 FFT：补零到 2 的幂、两次正变换、频域点乘、一次逆变换，最后四舍五入取回整数系数。
// 时间复杂度：O(n log n)，n 为不小于结果长度的 2 的幂；空间复杂度：O(n)，两个长度为 n 的复数数组。
class Solution {  // LeetCode 约定的题解类
    using cd = complex<double>;  // 用 complex<double> 表示复数，简写为 cd

    void fft(vector<cd>& a, bool invert) {  // 原地做快速傅里叶变换；invert 为真时做逆变换
        int n = a.size();  // 当前序列长度，必须是 2 的幂
        for (int i = 1, j = 0; i < n; ++i) {  // 第一步：位反转置换，把下标按二进制位翻转后重排
            int bit = n >> 1;  // 从最高位开始试探
            for (; j & bit; bit >>= 1) j ^= bit;  // 当前位为 1 就进位，模拟反转下标的二进制加法
            j ^= bit;  // 置上找到的这一位，得到与 i 位反转对应的下标 j
            if (i < j) swap(a[i], a[j]);  // 只在 i < j 时交换，避免把两个元素换回原位
        }
        for (int len = 2; len <= n; len <<= 1) {  // 按块长 2, 4, 8, ... 逐层合并
            double ang = 2 * M_PI / len * (invert ? -1 : 1);  // 本层单位根的角度，逆变换取共轭方向
            cd wlen(cos(ang), sin(ang));  // 本层的单位根 wlen = e^{i * ang}
            for (int i = 0; i < n; i += len) {  // 枚举每一块
                cd w(1, 0);  // 旋转因子从 1 开始
                int half = len >> 1;  // 每块前后两半的长度
                for (int j = 0; j < half; ++j) {  // 枚举块内的前半部分
                    cd u = a[i + j];  // 前半部分对应的元素
                    cd v = a[i + j + half] * w;  // 后半部分对应的元素乘上旋转因子
                    a[i + j] = u + v;  // 蝶形运算：和写回前半部分
                    a[i + j + half] = u - v;  // 蝶形运算：差写回后半部分
                    w *= wlen;  // 旋转因子推进到下一个单位根
                }
            }
        }
        if (invert)  // 逆变换在最后还需要额外除以长度 n
            for (cd& x : a) x /= n;  // 逐项除以 n 完成归一化
    }

public:  // 题解方法对外可见
    vector<long long> multiply(vector<int>& poly1, vector<int>& poly2) {  // poly1 / poly2：多项式的系数，下标即次数
        if (poly1.empty() || poly2.empty()) return {};  // 任一多项式为空则乘积为空
        int m = poly1.size() + poly2.size() - 1;  // 乘积多项式的项数
        int n = 1;  // 补零后的长度，取不小于 m 的最小 2 的幂
        while (n < m) n <<= 1;  // 不断翻倍直到足以容纳全部结果系数

        vector<cd> fa(n), fb(n);  // 两个长度为 n 的复数数组，多出来的位置都补 0
        for (int i = 0; i < n; ++i) {  // 把整数系数搬进复数数组
            fa[i] = i < poly1.size() ? cd(poly1[i], 0) : cd(0, 0);  // 超出第一个多项式长度的位置补 0
            fb[i] = i < poly2.size() ? cd(poly2[i], 0) : cd(0, 0);  // 超出第二个多项式长度的位置也补 0
        }

        fft(fa, false);  // 对第一个多项式做正变换
        fft(fb, false);  // 对第二个多项式做正变换
        for (int i = 0; i < n; ++i) fa[i] *= fb[i];  // 频域逐点相乘，等价于系数域的卷积
        fft(fa, true);  // 逆变换回到系数域

        vector<long long> res(m);  // 存放前 m 个有效系数
        for (int i = 0; i < m; ++i) res[i] = llround(fa[i].real());  // 四舍五入消除浮点误差并转成整数
        return res;  // 返回乘积多项式的系数
    }
};
