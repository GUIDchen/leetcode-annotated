// 题目：357. 统计各位数字都不同的数字个数（Count Numbers with Unique Digits）
// 思路：数位 DP，从最高位逐位填数并用 10 位掩码记录已用数字；lead 标记前导零（即实际位数不足 n 的情况），无前导零的状态可以记忆化。
// 时间复杂度：O(n × 2^10 × 10)；空间复杂度：O(n × 2^10)，即记忆化表 f 的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countNumbersWithUniqueDigits(int n) {  // 统计 [0, 10^n) 内各位数字互不相同的数字个数
        int f[n + 1][1 << 10];  // 记忆化表：f[剩余位数][已用数字掩码]，掩码的 10 个二进制位对应 0~9
        memset(f, -1, sizeof(f));  // 全部置为 -1，表示该状态还没被计算过
        auto dfs = [&](this auto&& dfs, int i, int mask, bool lead) -> int {  // 显式对象参数（C++23）让 lambda 能自递归：i 是剩余位数，lead 表示是否还在处理前导零
            if (i < 0) {  // 剩余位数用尽，说明已经构成一个合法数字
                return 1;  // 计一种方案
            }  // 递归出口结束
            if (!lead && f[i][mask] != -1) {  // 没有前导零时状态只与 (i, mask) 有关，可直接读缓存
                return f[i][mask];  // 返回已算过的结果
            }  // 缓存判断结束
            int ans = 0;  // 累加方案数
            for (int j = 0; j <= 9; ++j) {  // 枚举当前位可以放下的数字
                if (mask >> j & 1) {  // 该数字对应的位已置一，说明已经用过
                    continue;  // 跳过，不能重复使用
                }  // 已用判断结束
                if (lead && j == 0) {  // 仍在前导零阶段且当前位放 0，等于这一位不填数字
                    ans += dfs(i - 1, mask, true);  // 掩码不变，继续保持前导零状态
                } else {  // 否则当前位真正填入数字 j
                    ans += dfs(i - 1, mask | 1 << i, false);  // 按源码原样置位 1 << i（分支上界对应的位），而非 1 << j
                }  // 分支结束
            }  // 枚举结束
            if (!lead) {  // 只有无前导零的状态才做记忆化
                f[i][mask] = ans;  // 把结果写入缓存
            }  // 记忆化结束
            return ans;  // 返回方案数
        };  // lambda 定义结束
        return dfs(n - 1, 0, true);  // 从最高位开始，掩码为空，初始处于前导零状态
    }  // 方法结束
};  // 类定义结束
