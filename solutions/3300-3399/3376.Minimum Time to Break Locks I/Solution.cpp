// 题目：3376. 破解锁的最少时间 I（Minimum Time to Break Locks I）
// 思路：状态压缩 DP。mask 记录已破解的锁，第 cnt 把锁的能量 x = 1 + K*cnt，破解锁 j 需 ⌈strength[j]/x⌉ 次，记忆化 DFS 枚举下一把锁取最小值。
// 时间复杂度：O(2^n · n)；空间复杂度：O(2^n)，n 为锁的数量（n ≤ 8）。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int findMinimumTime(vector<int>& strength, int K) {  // strength：每把锁的强度；K：每破一把锁后能量增加的系数
        int n = strength.size();  // 锁的数量 n，n ≤ 8，因此可以用 2^n 个状态做状压 DP
        int f[1 << n];  // 记忆化数组：f[mask] 表示已破解 mask 中的锁后，破解剩余锁的最少总时间
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示该状态还没有被计算过
        int k = K;  // lambda 里以引用捕获 K，这里取个别名 k 让下面的表达式更短
        auto dfs = [&](this auto&& dfs, int i) -> int {  // C++23 递归 lambda：this auto&& dfs 是显式对象参数，使 lambda 能递归调用自己
            if (i == (1 << n) - 1) {  // mask 全 1 说明所有锁都已破解，到达递归终点
                return 0;  // 没有剩下的锁，剩余代价为 0
            }  // 递归终点处理结束
            if (f[i] != -1) {  // 该状态之前算过，直接复用缓存
                return f[i];  // 返回记忆化的最优值
            }  // 记忆化命中分支结束
            int cnt = __builtin_popcount(i);  // __builtin_popcount 统计 mask 中 1 的个数，也就是已经破解的锁数
            int x = 1 + k * cnt;  // 当前能量 x：破解第一把锁时为 1，之后每破解一把增加 K
            f[i] = INT_MAX;  // 先置为无穷大，方便下面的 min 逐个更新
            for (int j = 0; j < n; ++j) {  // 枚举下一把要破解的锁 j
                if (i >> j & 1 ^ 1) {  // 运算符优先级为 ((i >> j) & 1) ^ 1，即第 j 位为 0，说明锁 j 还没被破解
                    f[i] = min(f[i], dfs(i | 1 << j) + (strength[j] + x - 1) / x);  // 破解 j 需要 ⌈strength[j]/x⌉ 次，加上后续最优解，取最小
                }  // 选 j 的分支结束
            }  // 枚举下一把锁结束
            return f[i];  // 返回当前状态的最优值（后续调用会直接从 f 中取）
        };  // 递归 lambda 定义结束
        return dfs(0);  // 从「一把锁都没破解」的初始 mask 开始搜索，答案即最少时间
    }  // findMinimumTime 方法结束
};  // Solution 类定义结束
