// 题目：2338. 统计理想数组的数目（Count the Number of Ideal Arrays）
// 核心思路：把理想数组压缩成「相邻不同值构成的整除链」，每个值都可重复若干次；用 f[i][j] 统计长度为 j、以 i 结尾的整除链个数，再用组合数 C(n-1, j-1) 把 j 个不同值插回 n 个位置，求和即为答案。
// 时间复杂度：O(n*16 + 15*maxValue*log(maxValue))；空间复杂度：O(n*16 + maxValue*16)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int idealArrays(int n, int maxValue) {  // n：数组长度；maxValue：元素取值上限；返回值是理想数组个数取模
        const int mod = 1e9 + 7;  // 取模常量，防止计数溢出
        vector<vector<int>> c(n, vector<int>(16));  // c[i][j] 存组合数 C(i, j)；因为每条整除链最长约 15，16 列足够
        for (int i = 0; i < n; ++i) {  // 递推计算杨辉三角的第 0..n-1 行
            for (int j = 0; j <= i && j < 16; ++j) {  // 列 j 不超过 i，同时也不超过 16 列的上限
                if (j == 0) {  // 边界：C(i, 0) = 1
                    c[i][j] = 1;  // 组合数首列恒为 1
                } else {  // 一般情况：C(i, j) = C(i-1, j) + C(i-1, j-1)
                    c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;  // 用上一行两侧的组合数相加得到当前值，并随时取模
                }  // 分支结束
            }  // 列循环结束
        }  // 行循环结束，组合数表准备完毕

        vector<vector<long long>> f(maxValue + 1, vector<long long>(16));  // f[i][j]：长度为 j、以数值 i 结尾的整除链条数；16 列容纳最长链
        for (int i = 1; i <= maxValue; ++i) {  // 初始化：只含一个元素的链长度为 1
            f[i][1] = 1;  // 任何值自己单独成链，条数为 1
        }  // 初始化结束

        for (int j = 1; j < 15; ++j) {  // 按链长度从小到大递推，最长约 14，所以到 14 即可
            for (int i = 1; i <= maxValue; ++i) {  // 枚举链当前的末尾值 i
                for (int k = 2; k * i <= maxValue; ++k) {  // 枚举 i 的倍数 k*i 作为下一个更大的值（必须满足整除关系）
                    f[k * i][j + 1] = (f[k * i][j + 1] + f[i][j]) % mod;  // 把以 i 结尾长度为 j 的链延伸为以 k*i 结尾长度为 j+1 的链
                }  // 倍数循环结束
            }  // 末尾值循环结束
        }  // 链长度循环结束

        long long ans = 0;  // ans 累加所有理想数组的个数
        for (int i = 1; i <= maxValue; ++i) {  // 枚举压缩后整除链的最后一个值
            for (int j = 1; j < 16; ++j) {  // 枚举链中不同值的个数 j（即链长度）
                ans = (ans + f[i][j] * c[n - 1][j - 1]) % mod;  // 链有 j 个不同值，要用 C(n-1, j-1) 种方式放入 n 个位置并保持非降
            }  // 按列循环结束
        }  // 按值循环结束

        return ans;  // 返回答案（已对 1e9+7 取模）
    }  // idealArrays 方法结束
};  // Solution 类结束
