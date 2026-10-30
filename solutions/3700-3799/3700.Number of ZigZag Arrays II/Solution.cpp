// 题目：3700. 锯齿形数组的总数 II（Number of ZigZag Arrays II）
// 核心思路：把每个取值拆成「上升态」和「下降态」共 2m 个状态，构造 0/1 转移矩阵，再用矩阵快速幂求 trans 的 n-1 次方，最后乘上全 1 的初始向量并把所有分量求和。
// 复杂度：时间 O((2m)^3 * log n)；空间 O((2m)^2)，只存转移矩阵及其幂。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int zigZagArrays(int n, int l, int r) {  // 返回长度 n、取值在 [l, r] 内的锯齿形数组总数
        const int mod = 1e9 + 7;  // 结果对 1e9+7 取模
        int m = r - l + 1;  // 可选数字的个数，把区间 [l, r] 平移映射到 0..m-1
        int size = 2 * m;  // 状态数：前 m 个表示下降态，后 m 个表示上升态
        vector<vector<long long>> trans(size, vector<long long>(size));  // 转移矩阵，trans[新][旧] 表示旧状态能否走到新状态
        for (int x = 0; x < m; ++x) {  // 构造「下降态 -> 上升态」的边
            for (int y = 0; y < x; ++y) {  // 上一位取值 y 必须严格小于当前位取值 x
                trans[y][m + x] = 1;  // 由下降态 y 转到上升态 x，方案数记 1
            }  // 结束内层枚举
        }  // 结束第一类边构造
        for (int x = 0; x < m; ++x) {  // 构造「上升态 -> 下降态」的边
            for (int y = x + 1; y < m; ++y) {  // 上一位取值 y 必须严格大于当前位取值 x
                trans[m + y][x] = 1;  // 由上升态 y 转到下降态 x，方案数记 1
            }  // 结束内层枚举
        }  // 结束第二类边构造
        auto power = matrixPow(trans, n - 1, mod);  // 走 n-1 步后的转移矩阵，即所有长度为 n 的方案
        vector<long long> init(size, 1);  // 长度为 1 时每个状态各 1 种初始方案
        auto result = multiply(power, init, mod);  // 用矩阵乘向量得到长度 n 时每个状态的方案数
        long long ans = 0;  // ans 汇总所有结尾状态的方案数
        for (long long v : result) {  // 枚举每个可能的状态
            ans = (ans + v) % mod;  // 累加该状态下的方案数
        }  // 结束汇总
        return ans;  // 返回锯齿形数组总数
    }  // 结束 zigZagArrays

private:  // 以下为内部辅助函数
    vector<long long> multiply(vector<vector<long long>>& mat, vector<long long>& vec, int mod) {  // 矩阵乘向量
        int n = mat.size();  // 方阵的阶，同时也是向量的长度
        vector<long long> res(n);  // 存放乘积向量
        for (int i = 0; i < n; ++i) {  // 逐行计算结果向量的第 i 个分量
            long long sum = 0;  // 第 i 个分量先清零
            for (int j = 0; j < n; ++j) {  // 遍历该行的每个元素做点积
                sum = (sum + mat[i][j] * vec[j]) % mod;  // 累加点积并随时取模防溢出
            }  // 结束点积累加
            res[i] = sum;  // 写回该分量
        }  // 结束逐行计算
        return res;  // 返回矩阵乘向量的结果
    }  // 结束矩阵乘向量
    vector<vector<long long>> multiply(  // 重载：方阵乘方阵
        vector<vector<long long>>& a, vector<vector<long long>>& b, int mod) {  // a、b 为同阶方阵，mod 为取模常数
        int n = a.size();  // 方阵的阶
        vector<vector<long long>> res(n, vector<long long>(n));  // 结果方阵先全部置 0
        for (int i = 0; i < n; ++i) {  // 枚举结果的行
            for (int k = 0; k < n; ++k) {  // 枚举中间维度，i-k-j 顺序替换 i-j-k 以减少乘法次数
                if (a[i][k] == 0) {  // a 的该元素为 0 时整段乘法都可跳过
                    continue;  // 直接进入下一个 k
                }  // 结束零元素剪枝
                long long aik = a[i][k];  // 把公共因子提到内层循环之外
                for (int j = 0; j < n; ++j) {  // 枚举结果的列
                    if (b[k][j] == 0) {  // b 的该元素为 0 时这一项贡献为 0
                        continue;  // 跳过这一项
                    }  // 结束零元素剪枝
                    res[i][j] = (res[i][j] + aik * b[k][j]) % mod;  // 累乘累加并取模
                }  // 结束列枚举
            }  // 结束中间维度枚举
        }  // 结束行枚举
        return res;  // 返回方阵乘积
    }  // 结束方阵乘方阵
    vector<vector<long long>> matrixPow(vector<vector<long long>>& mat, long long exp, int mod) {  // 方阵快速幂
        int n = mat.size();  // 方阵的阶
        vector<vector<long long>> res(n, vector<long long>(n));  // 结果矩阵初始化为单位矩阵
        for (int i = 0; i < n; ++i) {  // 主对角线置 1
            res[i][i] = 1;  // 单位矩阵的对角元为 1
        }  // 结束单位矩阵初始化
        while (exp > 0) {  // 按二进制位从低到高处理指数
            if (exp & 1) {  // 当前二进制位为 1 时需要把这一份乘进结果
                res = multiply(res, mat, mod);  // 累乘当前的 mat
            }  // 结束当前位判断
            mat = multiply(mat, mat, mod);  // mat 自乘，为下一位准备平方
            exp >>= 1;  // 指数右移一位
        }  // 结束二进制幂
        return res;  // 返回 mat 的 exp 次方
    }  // 结束方阵快速幂
};  // 结束题解类
