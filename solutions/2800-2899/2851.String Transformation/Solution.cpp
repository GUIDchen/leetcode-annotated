// 题目：2851. 字符串转换（String Transformation）
// 核心思路：k 次右移等价于「旋转量」在 0 与非 0 之间跳转，用 Z 算法找出 t 对应的旋转量，再用矩阵快速幂求 k 步的方案数。
// 时间复杂度：O(n + log k)；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
    const int M = 1000000007;  // 取模常量，所有加乘运算都在模 1e9+7 下进行

    int add(int x, int y) {  // 模意义下的加法：相加后若达到模数就减一次模数
        if ((x += y) >= M) {  // 先把 y 累加到 x 上再与模数比较
            x -= M;  // 达到模数就减去模数，保证结果落在 [0, M)
        }  // 结束 if 分支
        return x;  // 返回模意义下的和
    }  // 结束函数体

    int mul(long long x, long long y) {  // 模意义下的乘法，参数用 long long 承载中间乘积防溢出
        return x * y % M;  // 先乘再取模
    }  // 结束函数体

    vector<int> getz(const string& s) {  // Z 算法：z[i] 表示 s[i..] 与 s 本身的最长公共前缀长度
        const int n = s.length();  // 字符串长度
        vector<int> z(n);  // z 数组初始化为 0，z[0] 按惯例保留 0
        for (int i = 1, left = 0, right = 0; i < n; ++i) {  // i 从 1 开始；[left, right] 是当前最靠右的已匹配区间
            if (i <= right && z[i - left] <= right - i) {  // 落在已知区间内，且可直接继承对称位置的答案而不越过右端
                z[i] = z[i - left];  // 直接复制 z[i - left]
            } else {  // 否则需要真正逐字符比较扩展
                for (z[i] = max(0, right - i + 1); i + z[i] < n && s[i + z[i]] == s[z[i]]; ++z[i])  // 从区间右端外一格起步（至少 0），逐字符比较并自增长度
                    ;  // 循环体为空，长度的增长写在循环条件里
            }  // 结束 else 分支
            if (i + z[i] - 1 > right) {  // 若新的右端超过了已知最右端，就更新区间
                left = i;  // 新区间左端
                right = i + z[i] - 1;  // 新区间右端
            }  // 结束 if 分支
        }  // 结束 for 循环
        return z;  // 返回 z 数组
    }  // 结束函数体

    vector<vector<int>> mul(const vector<vector<int>>& a, const vector<vector<int>>& b) {  // 矩阵乘法（重载）：a 为 m x n，b 为 n x p
        const int m = a.size(), n = a[0].size(), p = b[0].size();  // 分别取出三个维度
        vector<vector<int>> r(m, vector<int>(p));  // 结果矩阵 m x p，初值全 0
        for (int i = 0; i < m; ++i) {  // 枚举结果的行
            for (int j = 0; j < n; ++j) {  // 枚举公共累加维度
                for (int k = 0; k < p; ++k) {  // 枚举结果的列
                    r[i][k] = add(r[i][k], mul(a[i][j], b[j][k]));  // 每一项在模意义下累加到 r[i][k]
                }  // 结束 for 循环
            }  // 结束 for 循环
        }  // 结束 for 循环
        return r;  // 返回结果矩阵
    }  // 结束函数体

    vector<vector<int>> pow(const vector<vector<int>>& a, long long y) {  // 矩阵快速幂：求 a 的 y 次方
        const int n = a.size();  // 方阵阶数
        vector<vector<int>> r(n, vector<int>(n));  // 结果初始化为零矩阵
        for (int i = 0; i < n; ++i) {  // 主对角线置 1，构成单位矩阵
            r[i][i] = 1;  // 单位矩阵对角线
        }  // 结束 for 循环
        auto x = a;  // 拷贝一份底数，供反复自乘
        for (; y; y >>= 1) {  // 二进制拆分指数，每右移一位代表指数翻倍
            if (y & 1) {  // 当前二进制位为 1 时把对应的幂乘进结果
                r = mul(r, x);  // 累乘到结果矩阵
            }  // 结束 if 分支
            x = mul(x, x);  // 底数自乘，对应指数翻倍
        }  // 结束 for 循环
        return r;  // 返回 a 的 y 次方
    }  // 结束函数体

public:  // 对外公开的接口区域
    int numberOfWays(string s, string t, long long k) {  // s 与 t 为等长字符串，k 是允许的右移次数
        const int n = s.length();  // 字符串长度 n
        const auto dp = pow({{0, 1}, {n - 1, n - 2}}, k)[0];  // 转移矩阵 [[0,1],[n-1,n-2]] 的 k 次方，取第一行即 dp[k][0] 与 dp[k][1]
        s.append(t);  // 先把 t 接到 s 后面
        s.append(t);  // 再接一次 t，得到 s + t + t 便于用 Z 算法枚举所有旋转起点
        const auto z = getz(s);  // 对拼接后的新串求 z 数组
        const int m = n + n;  // 只需检查偏移 n .. 2n-1 这一段
        int r = 0;  // 累计合法旋转量的方案数
        for (int i = n; i < m; ++i) {  // 枚举 t 在拼接串中的每个起点
            if (z[i] >= n) {  // 前缀匹配长度达到 n，说明 t 就是 s 的一个循环移位
                r = add(r, dp[!!(i - n)]);  // 偏移 0 用 dp[0]，非零偏移共用 dp[1]
            }  // 结束 if 分支
        }  // 结束 for 循环
        return r;  // 返回总方案数
    }  // 结束函数体
};  // 结束类定义