// 题目：2403. 杀死所有怪物的最短时间（Minimum Time to Kill All Monsters）
// 思路：状态压缩 DP，mask 表示还没杀死的怪物集合；已杀数量决定每分钟伤害，记忆化搜索对每种选择取最小耗时。
// 时间复杂度：O(2^n × n)，每个状态枚举 n 只怪物；空间复杂度：O(2^n)，记忆化数组 f 保存每个状态的最优值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumTime(vector<int>& power) {  // power：每只怪物的血量，返回杀光所有怪物的最短时间
        int n = power.size();  // n：怪物总数
        long long f[1 << n];  // f[mask]：剩余怪物集合为 mask 时杀光它们所需的最短时间
        memset(f, -1, sizeof(f));  // 初始化为 -1，表示该状态还没计算过
        auto dfs = [&](this auto&& dfs, int mask) -> long long {  // 定义递归 lambda，显式传入自身以支持递归调用
            if (mask == 0) {  // 没有怪物剩余，递归边界
                return 0;  // 不需要再花时间
            }
            if (f[mask] != -1) {  // 该状态已经计算过
                return f[mask];  // 直接返回记忆化结果，避免重复搜索
            }
            f[mask] = LLONG_MAX;  // 先设为无穷大，方便后面取最小值
            int gain = 1 + (n - __builtin_popcount(mask));  // 每分钟伤害：1 + 已杀怪物数量（总数减剩余数量）
            for (int i = 0; i < n; ++i) {  // 枚举每一只怪物，尝试下一个就杀它
                if (mask >> i & 1) {  // 第 i 只怪物还活着
                    f[mask] = min(f[mask], dfs(mask ^ (1 << i)) + (power[i] + gain - 1) / gain);  // 杀它耗时向上取整，再加上剩余怪物的最优解
                }
            }
            return f[mask];  // 返回当前状态的最小总时间
        };
        return dfs((1 << n) - 1);  // 初始时 n 只怪物全部活着，mask 是低 n 位全为 1
    }
};
