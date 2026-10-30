// 3539. 魔法序列的数组乘积之和 / Find Sum of Array Product of Magical Sequences
// 核心思路：按二进制位做数位 DP，枚举每个数被选的次数 t，用组合数分配下标、幂次贡献乘积，进位逐位消耗统计 popcount 恰为 k 的方案数。
// 复杂度：时间 O(n·m·k·m·log(max))（含快速幂），空间 O(n·m·k·N) 的记忆化数组。
const int N = 31;  // 组合数的最大规模（m、k 不超过 30）
const long long MOD = 1'000'000'007;  // 取模常数

long long f[N], g[N];  // f 存阶乘，g 存阶乘的模逆元

long long qpow(long long a, long long k) {  // 快速幂：返回 a^k mod MOD
    long long res = 1;  // 结果初值为 1
    while (k) {  // 指数不为 0 时继续
        if (k & 1) res = res * a % MOD;  // 当前二进制位为 1 则把这一份乘进结果
        a = a * a % MOD;  // 底数平方
        k >>= 1;  // 指数右移一位
    }  // while 循环结束
    return res;  // 返回 a^k mod MOD
}  // 函数结束

int init = []() {  // 利用全局变量初始化，预先算好阶乘与逆元
    f[0] = g[0] = 1;  // 0! = 1，其逆元也是 1
    for (int i = 1; i < N; ++i) {  // 从小到大逐个计算
        f[i] = f[i - 1] * i % MOD;  // i! = (i-1)! × i
        g[i] = qpow(f[i], MOD - 2);  // 用费马小定理求 i! 的逆元
    }  // 循环结束
    return 0;  // 返回值仅用于触发初始化
}();  // 立即执行该 lambda

long long comb(int m, int n) {  // 计算组合数 C(m, n)
    return f[m] * g[n] % MOD * g[m - n] % MOD;  // m! / (n! (m-n)!)，除法用乘逆元实现
}  // 函数结束

class Solution {  // 定义题解类
    vector<vector<vector<vector<long long>>>> dp;  // 记忆化数组 dp[i][j][k][st]

    long long dfs(int i, int j, int k, int st) {  // 处理前 i 个数、还需选 j 个、剩余进位下限 k、当前进位 st
        if (k < 0 || (i == nums.size() && j > 0)) {  // 进位已为负，或所有数用完却还没选够 j 个
            return 0;  // 该方案不合法，贡献 0
        }  // if 语句结束
        if (i == nums.size()) {  // 所有数都已处理完毕
            while (st > 0) {  // 把剩余进位逐位消耗
                k -= (st & 1);  // 减去该二进制位上 1 的个数
                st >>= 1;  // 进位右移一位
            }  // while 循环结束
            return k == 0 ? 1 : 0;  // 恰好消耗掉 k 个 1 则计 1 种方案
        }  // if 语句结束

        long long& res = dp[i][j][k][st];  // 引用记忆化位置，避免重复拷贝
        if (res != -1) {  // 该状态已经算过
            return res;  // 直接返回缓存值
        }  // if 语句结束

        res = 0;  // 累加初值为 0
        for (int t = 0; t <= j; ++t) {  // 枚举当前数字被选中的次数 t
            int nt = t + st;  // 加上已有进位
            int nk = k - (nt & 1);  // 当前二进制位贡献的 1 从 k 中扣掉
            long long p = qpow(nums[i], t);  // nums[i] 的 t 次幂
            long long tmp = comb(j, t) * p % MOD * dfs(i + 1, j - t, nk, nt >> 1) % MOD;  // 选出 t 个位置 × 幂次 × 子问题方案数
            res = (res + tmp) % MOD;  // 累加并取模
        }  // 循环结束
        return res;  // 返回该状态的方案数
    }  // 方法结束

public:  // 公有方法区
    int magicalSum(int m, int k, vector<int>& nums) {  // 主函数：返回所有魔法序列的数组乘积之和
        int n = nums.size();  // 元素个数
        this->nums = nums;  // 保存到成员变量，供 dfs 使用
        dp.assign(n + 1, vector<vector<vector<long long>>>(m + 1, vector<vector<long long>>(k + 1, vector<long long>(N, -1))));  // 记忆化数组全部初始化为 -1
        return dfs(0, m, k, 0);  // 从第 0 个数、还需选 m 个、剩余 k 个 1、进位 0 开始
    }  // 方法结束

private:  // 私有成员区
    vector<int> nums;  // 保存的数组 nums
};  // 类定义结束
