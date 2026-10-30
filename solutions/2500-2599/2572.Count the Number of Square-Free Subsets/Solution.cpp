// 题目：2572. 无平方子集计数（Count the Number of Square-Free Subsets）
// 思路：把每个数值映射成「它含有哪些质因子」的 10 位掩码，做状压 0/1 背包 DP；含平方因子的数不能入选，数字 1 只能提供 2 的幂次种选择。
// 时间复杂度：O(30 × 2^10)，枚举 30 个数值与 1024 个掩码；空间复杂度：O(2^10)，DP 数组大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int squareFreeSubsets(vector<int>& nums) {  // nums：输入数组，返回其中无平方因子的子集个数
        int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};  // 1..30 内的全部质数，用 10 个二进制位分别表示
        int cnt[31]{};  // cnt[x] 记录数值 x 在 nums 中出现的次数
        for (int& x : nums) {  // 遍历输入数组，统计每个数值的出现次数
            ++cnt[x];  // 数值 x 的计数加一
        }
        int n = 10;  // 质数个数，也就是掩码的位数
        const int mod = 1e9 + 7;  // 取模常量，防止答案超出范围
        vector<long long> f(1 << n);  // f[mask]：已选质因子集合恰好为 mask 的子集方案数
        f[0] = 1;  // 什么都不选也是一种方案（空集）
        for (int i = 0; i < cnt[1]; ++i) {  // 数字 1 不含任何质因子，cnt[1] 个 1 可以自由取舍
            f[0] = f[0] * 2 % mod;  // 每个 1 都有选或不选两种可能，方案数翻倍
        }
        for (int x = 2; x < 31; ++x) {  // 从小到大枚举可能被选中的数值
            if (cnt[x] == 0 || x % 4 == 0 || x % 9 == 0 || x % 25 == 0) {  // 该数值没出现过，或是 4/9/25 的倍数（含平方因子），不能入选
                continue;  // 直接跳过这个数值
            }
            int mask = 0;  // 用来记录当前数值的质因子集合
            for (int i = 0; i < n; ++i) {  // 逐个质数检查它是否能整除 x
                if (x % primes[i] == 0) {  // x 含有质因子 primes[i]
                    mask |= 1 << i;  // 在掩码的第 i 位上打标记
                }
            }
            for (int state = (1 << n) - 1; state; --state) {  // 倒序枚举状态，保证同一个数值最多被用一次（0/1 背包写法）
                if ((state & mask) == mask) {  // 只有已经包含 x 全部质因子的状态，才能由 state ^ mask 转移而来
                    f[state] = (f[state] + 1LL * cnt[x] * f[state ^ mask]) % mod;  // 选一个 x 就有 cnt[x] 种选法，累加方案数并取模
                }
            }
        }
        long long ans = -1;  // 从 -1 开始，最后把「一个数都不选」的空集减掉
        for (int i = 0; i < 1 << n; ++i) {  // 累加所有掩码下的方案数
            ans = (ans + f[i]) % mod;  // 逐步累加并取模
        }
        return ans;  // 返回无平方子集的个数
    }
};