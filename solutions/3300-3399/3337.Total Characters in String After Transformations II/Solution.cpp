// 题目：3337. 字符串转换后的长度 II（Total Characters in String After Transformations II）
// 思路：用 26×26 转移矩阵描述「字母 i 一步能变成哪些字母」，矩阵快速幂求出 t 步的转移矩阵，再让初始字母计数行向量右乘它，最后各分量求和。
// 时间复杂度：O(M^3 log t)，M = 26 为常数；空间复杂度：O(M^2)，矩阵大小固定。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    static constexpr int MOD = 1e9 + 7;  // 取模常量，防止计数溢出
    static constexpr int M = 26;  // 字母表大小，也是转移矩阵的维度

    using Matrix = vector<vector<int>>;  // 矩阵类型别名，用二维 vector 存放 26×26 的整数矩阵

    Matrix matmul(const Matrix& a, const Matrix& b) {  // 朴素矩阵乘法：a 是 n×p，b 是 p×q，结果对 MOD 取模
        int n = a.size(), p = b.size(), q = b[0].size();  // 取出三个维度：结果矩阵是 n×q，中间维是 p
        Matrix res(n, vector<int>(q, 0));  // 结果矩阵先全部初始化为 0
        for (int i = 0; i < n; ++i) {  // 枚举结果矩阵的行 i
            for (int k = 0; k < p; ++k) {  // 枚举中间维 k，即 a 的列号 / b 的行号
                if (a[i][k]) {  // 稀疏剪枝：系数 a[i][k] 为 0 时整项贡献为 0，直接跳过内层循环
                    for (int j = 0; j < q; ++j) {  // 枚举结果矩阵的列 j
                        res[i][j] = (res[i][j] + 1LL * a[i][k] * b[k][j] % MOD) % MOD;  // 用 1LL 把乘法提升到 64 位，避免 int 溢出，乘完先取模再累加取模
                    }
                }
            }
        }
        return res;  // 返回乘积矩阵
    }

    Matrix matpow(Matrix mat, int power) {  // 矩阵快速幂：返回 mat 的 power 次方（mat 按值传递，可在函数内自乘）
        Matrix res(M, vector<int>(M, 0));  // 结果矩阵的容器，先全部置 0
        for (int i = 0; i < M; ++i) res[i][i] = 1;  // 对角线置 1，得到单位矩阵（相当于幂运算的初值 1）
        while (power) {  // 二进制拆分指数，逐位处理
            if (power % 2) res = matmul(res, mat);  // 当前最低位为 1，说明这一位对应的幂要乘进结果
            mat = matmul(mat, mat);  // 底数自乘，对应指数翻倍，准备贡献下一位
            power /= 2;  // 指数右移一位（整除 2）
        }
        return res;  // 返回幂矩阵
    }

    int lengthAfterTransformations(string s, int t, vector<int>& nums) {  // s：原字符串；t：变换次数；nums[i]：字母 i 一次能扩展出的字母个数
        vector<int> cnt(M, 0);  // cnt[c] 统计原字符串中字母 c 的出现次数
        for (char c : s) {  // 遍历原字符串的每个字符
            cnt[c - 'a']++;  // 字符减 'a' 映射到 0..25 的下标后自增计数
        }

        Matrix matrix(M, vector<int>(M, 0));  // 构造转移矩阵：matrix[i][j] = 1 表示字母 i 一步能变成字母 j
        for (int i = 0; i < M; ++i) {  // 枚举起始字母 i
            for (int j = 1; j <= nums[i]; ++j) {  // 字母 i 能变成它后面的第 1..nums[i] 个字母（超出 z 会回绕）
                matrix[i][(i + j) % M] = 1;  // (i + j) % 26 把目标字母循环映射回 0..25，标记这条转移边
            }
        }

        Matrix cntMat(1, vector<int>(M));  // 只有一行的计数矩阵（行向量），表示 0 步时各字母的数量
        for (int i = 0; i < M; ++i) cntMat[0][i] = cnt[i];  // 把初始计数填进这唯一的行

        Matrix factor = matpow(matrix, t);  // 快速幂求出走 t 步的总转移矩阵
        Matrix result = matmul(cntMat, factor);  // 行向量右乘转移矩阵，得到 t 步后各字母的数量

        int ans = 0;  // 答案累加器
        for (int x : result[0]) {  // 遍历结果行向量中的每个字母数量
            ans = (ans + x) % MOD;  // 累加并取模，每个 x 本身已经取过模
        }

        return ans;  // 所有字母数量之和就是变换后字符串的长度
    }
};  // 类定义结束
