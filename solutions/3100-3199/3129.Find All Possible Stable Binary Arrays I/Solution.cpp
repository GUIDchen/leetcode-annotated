// 题目：3129. 找出所有稳定的二进制数组 I（Find All Possible Stable Binary Arrays I）
// 思路：记忆化搜索 + 容斥，dfs(i, j, k) 表示剩余 i 个 0、j 个 1 且末尾为 k 的方案数，转移时减去连续段超过 limit 的部分。
// 时间复杂度：O(zero * one)，每个状态只计算一次；空间复杂度：O(zero * one)，记忆化数组占用的空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfStableArrays(int zero, int one, int limit) {  // zero、one 分别是 0 与 1 的个数，limit 是同一数字连续出现的最长长度
        const int mod = 1e9 + 7;  // 答案取模的模数
        using ll = long long;  // 给 long long 起短名字，避免转移中的加法在 int 上溢出
        vector<vector<array<ll, 2>>> f = vector<vector<array<ll, 2>>>(zero + 1, vector<array<ll, 2>>(one + 1, {-1, -1}));  // 记忆化表 f[i][j][k]：剩 i 个 0、j 个 1 且末尾为 k 的方案数，-1 表示尚未计算
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> ll {  // C++23 的递归 lambda：把自身当首参传入以便自调用；k=0 表示末尾是 0，k=1 表示末尾是 1
            if (i < 0 || j < 0) {  // 容斥时下标可能被减成负数，越界说明这种取法不合法
                return 0;  // 不合法的取法贡献 0 种方案
            }  // 越界判断结束
            if (i == 0) {  // 0 已经用完，剩下的一定全是 1
                return k == 1 && j <= limit;  // 只有末尾是 1 且剩余 1 的个数不超过 limit 才合法，bool 隐式转成 ll
            }  // i == 0 分支结束
            if (j == 0) {  // 1 已经用完，剩下的一定全是 0
                return k == 0 && i <= limit;  // 只有末尾是 0 且剩余 0 的个数不超过 limit 才合法
            }  // j == 0 分支结束
            ll& res = f[i][j][k];  // 用引用取出记忆化单元，后面直接往里写结果
            if (res != -1) {  // 该状态已经算过
                return res;  // 直接复用旧结果，避免重复搜索
            }  // 缓存命中分支结束
            if (k == 0) {  // 末尾是 0，本次往末尾再追加一个 0
                res = (dfs(i - 1, j, 0) + dfs(i - 1, j, 1) - dfs(i - limit - 1, j, 1) + mod) % mod;  // 用掉一个 0 后末尾可以是 0 或 1，再容斥掉「0 连续长度超过 limit」的非法部分；加 mod 防止减法出现负数
            } else {  // 否则末尾是 1，本次往末尾再追加一个 1
                res = (dfs(i, j - 1, 0) + dfs(i, j - 1, 1) - dfs(i, j - limit - 1, 0) + mod) % mod;  // 对称地：用掉一个 1，再容斥掉「1 连续长度超过 limit」的非法部分
            }  // 两种末尾情况的分支结束
            return res;  // 返回本状态的方案数
        };  // lambda 定义结束
        return (dfs(zero, one, 0) + dfs(zero, one, 1)) % mod;  // 第一个数字既可以是 0 也可以是 1，两种末尾情况相加再取模
    }  // 方法体结束
};  // 类定义结束
