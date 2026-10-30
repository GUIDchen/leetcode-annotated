// 题目：3351. 好子序列的元素之和（Sum of Good Subsequences）
// 思路：按值域做 DP，f[v]/g[v] 分别是以值 v 结尾的好子序列元素和与个数，逐个元素从 v-1、v、v+1 三个来源并入后再累加所有 f。
// 时间复杂度：O(n + max(nums))；空间复杂度：O(max(nums))，两个长度 max(nums)+1 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfGoodSubsequences(vector<int>& nums) {  // nums：输入数组
        const int mod = 1e9 + 7;  // 取模常数 1e9 + 7，避免中间结果溢出
        int mx = ranges::max(nums);  // C++20 ranges::max 求值域上界，DP 只需覆盖 0..mx

        vector<long long> f(mx + 1), g(mx + 1);  // f[v]：以值 v 结尾的好子序列元素之和；g[v]：以值 v 结尾的好子序列个数
        for (int x : nums) {  // 逐个把元素 x 并入 DP
            f[x] += x;  // 长度 1 的子序列 [x] 单独成立，元素和加上 x
            g[x] += 1;  // 这种只含 x 的子序列个数加一

            if (x > 0) {  // 从值 x-1 迁移过来：好子序列的相邻元素差必须为 1
                f[x] = (f[x] + f[x - 1] + g[x - 1] * x % mod) % mod;  // 新和 = 原有的 + 以 x-1 结尾的旧和 + 每个旧序列追加 x 的增量 g[x-1] * x
                g[x] = (g[x] + g[x - 1]) % mod;  // 个数同步累加，取模避免溢出
            }  // 结束 x-1 方向的迁移

            if (x + 1 <= mx) {  // 从值 x+1 迁移过来：差值同样为 1，x 可以接在值更大的序列前面
                f[x] = (f[x] + f[x + 1] + g[x + 1] * x % mod) % mod;  // 同理，把 x 放到以 x+1 结尾的序列之前，增量仍是 g[x+1] * x
                g[x] = (g[x] + g[x + 1]) % mod;  // 个数同步累加，取模避免溢出
            }  // 结束 x+1 方向的迁移
        }  // 结束单元素并入

        return accumulate(f.begin(), f.end(), 0LL) % mod;  // 把「以任意值结尾」的好子序列元素和全部累加，再取模得到答案
    }  // 结束题解方法
};  // 结束题解类
