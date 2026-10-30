// 4028. 得到旋转回文字符串的最少操作次数 II / Minimum Operations to Make a Rotated Palindrome II
// 核心思路：先把字母修改代价按 26 次单位根展开成频率求和，再用 FFT 做循环相关，一次性求出每个旋转位置作为回文中心时的最小修改代价，最后叠加旋转次数 k 取最小值。
// 复杂度：时间 O(14 · M log M + 26^2)，空间 O(M)（M 为不小于 2n 的 2 的幂）。
class Solution {  // 题解类定义
    using cd = complex<double>;  // 复数类型别名，供 FFT 使用
    const double PI = acos(-1);  // 圆周率常量

    void fft(vector<cd>& a, bool inv) {  // 迭代式快速傅里叶变换，inv 为真时做逆变换
        int n = a.size();  // 变换长度（应当是 2 的幂）

        for (int i = 1, j = 0; i < n; i++) {  // 第一步：按二进制反转重新排列所有元素
            int bit = n >> 1;  // 反转位从最高位开始试探

            while (j & bit) {  // 若当前反转位已被置上，则清除并继续向低位走
                j ^= bit;  // 清除该位
                bit >>= 1;  // 降到下一位
            }  // 结束反转位调整

            j ^= bit;  // 置上第一个为 0 的反转位，得到 i 的二进制反转下标

            if (i < j) {  // 只在 i 小于其反转下标时交换，避免重复交换
                swap(a[i], a[j]);  // 把元素交换到二进制反转后的位置
            }  // 结束本次交换
        }  // 结束二进制反转重排

        for (int len = 2; len <= n; len <<= 1) {  // 第二步：按块长倍增做蝶形合并
            double ang = 2.0 * PI / len * (inv ? -1 : 1);  // 当前块长对应的旋转因子角度，逆变换取负角
            cd wlen(cos(ang), sin(ang));  // 构造单位旋转因子 e^{i·ang}

            for (int i = 0; i < n; i += len) {  // 枚举每个块的起点
                cd w(1);  // 块内的旋转因子从 1 开始

                for (int j = 0; j < len / 2; j++) {  // 枚举块内前半部分的元素
                    cd u = a[i + j];  // 前半部分元素
                    cd v = a[i + j + len / 2] * w;  // 后半部分元素乘以旋转因子

                    a[i + j] = u + v;  // 蝶形运算的加法支路
                    a[i + j + len / 2] = u - v;  // 蝶形运算的减法支路

                    w *= wlen;  // 旋转因子自乘一次，向前推进一格
                }  // 结束块内枚举
            }  // 结束块起点枚举
        }  // 结束块长倍增

        if (inv) {  // 逆变换最后需要把结果除以长度 n
            for (auto& x : a) {  // 遍历所有元素
                x /= n;  // 做归一化
            }  // 结束归一化
        }  // 结束逆变换分支
    }  // 结束 fft 函数

public:  // 公有成员：判题器调用的接口
    int minOperations(string s) {  // 返回把 s 旋转后变成回文串所需的最少操作次数（旋转 + 修改字母）
        int n = s.size();  // 字符串长度

        int size = 1;  // FFT 长度，取不小于 2n 的最小 2 的幂
        while (size < 2 * n) {  // 不断翻倍，直到长度足够
            size <<= 1;  // 长度翻倍
        }  // 结束长度调整

        vector<int> nums(n);  // 把每个字符映射成 0..25 的整数
        for (int i = 0; i < n; i++) {  // 逐位转换
            nums[i] = s[i] - 'a';  // 字符减去 'a' 得到字母编号
        }  // 结束字符映射

        vector<double> cost(26);  // cost[t] 是代价函数按 26 次单位根展开后的第 t 个频率系数

        for (int t = 0; t < 26; t++) {  // 枚举频率 t（0..25）
            for (int z = 0; z < 26; z++) {  // 枚举字母间的环形距离 z（0..25）
                int d = min(z, 26 - z);  // 字母相差 z 个位置时的最小修改代价（环形距离）

                cost[t] += d * cos(-2.0 * PI * t * z / 26);  // 对代价函数做离散傅里叶变换，累加余弦项
            }  // 结束距离枚举
        }  // 结束频率枚举

        vector<double> dp(n);  // dp[c] 记录配对中心落在 c 时的累计修改代价

        vector<cd> a(size);  // FFT 的输入序列
        vector<cd> b(size);  // 保存相关运算结果序列

        for (int t = 0; t < 14; t++) {  // 只需枚举 0..13 共 14 个频率，另一半由共轭对称性得到
            double theta = 2.0 * PI * t / 26;  // 第 t 个频率对应的角度

            for (int i = 0; i < n; i++) {  // 把每个字符映射到复平面单位圆上
                double angle = theta * nums[i];  // 该字符对应的相位
                a[i] = cd(cos(angle), sin(angle));  // 填入 e^{i·angle}
            }  // 结束字符映射

            for (int i = n; i < size; i++) {  // 其余位置补零，避免循环卷积混叠
                a[i] = 0;  // 补零
            }  // 结束补零

            fft(a, false);  // 对输入序列做正变换

            for (int i = 0; i < size; i++) {  // 逐点相乘并取共轭，等价于在时域做相关运算
                cd x = a[i];  // 当前频点的值
                cd y = conj(a[(size - i) & (size - 1)]);  // 取共轭对称位置的共轭值

                b[i] = x * y;  // 频域相乘对应时域卷积
                b[i] = conj(b[i]);  // 再取共轭，得到所需的相关结果
            }  // 结束频点处理

            fft(b, false);  // 把相关结果变换回时域

            double mult = (t == 0 || t == 13) ? 1.0 : 2.0;  // t = 0 与 t = 13 是实轴上的双重频率，只算一次
            double factor = mult * cost[t] / size;  // 合并系数，其中包含除以 FFT 长度 size

            for (int c = 0; c < n; c++) {  // 枚举旋转后每个配对中心
                dp[c] += factor * (b[c].real() + b[c + n].real());  // 累加该位置在两段长度 n 窗口上的相关值之和
            }  // 结束配对中心枚举
        }  // 结束频率枚举

        long long ans = LLONG_MAX;  // 答案初值为无穷大

        for (int k = 0; k < n; k++) {  // 枚举旋转次数 k
            int c = (2 * k + n - 1) % n;  // 旋转 k 次后，配对中心在相关数组中的下标
            long long d = llround(dp[c] / 52.0);  // 除以 52（26 个频率 × 2 段长度 n 的窗口）并四舍五入，还原真实修改代价

            ans = min(ans, k + d);  // 总操作次数 = 旋转次数 + 字母修改代价
        }  // 结束旋转枚举

        return (int) ans;  // 返回最少操作次数
    }  // 结束函数
};  // 结束类定义