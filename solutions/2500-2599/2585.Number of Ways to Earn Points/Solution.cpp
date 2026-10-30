// 题目：2585. 获得分数的方法数（Number of Ways to Earn Points）
// 思路：分组多重背包计数 DP。f[i][j] 表示只用前 i 种题型恰好得 j 分的方法数，枚举第 i 种题做 k 道（0<=k<=count），由 f[i-1][j-k*marks] 转移并对 1e9+7 取模。
// 时间复杂度：O(n * target * maxCount)；空间复杂度：O(n * target)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int waysToReachTarget(int target, vector<vector<int>>& types) {  // target 为目标总分，types 每项是 [数量, 每题分数]
        int n = types.size();  // 题型总数
        const int mod = 1e9 + 7;  // 计数取模常量，防止溢出
        int f[n + 1][target + 1];  // f[i][j]：前 i 种题型恰好凑出 j 分的方法数
        memset(f, 0, sizeof(f));  // 全部初始化为 0，表示暂不可达
        f[0][0] = 1;  // 边界：不选任何题就得到 0 分，有 1 种方案
        for (int i = 1; i <= n; ++i) {  // 逐种题型做递推
            int count = types[i - 1][0], marks = types[i - 1][1];  // 第 i 种题的可做数量与每题分数
            for (int j = 0; j <= target; ++j) {  // 枚举当前要凑出的总分
                for (int k = 0; k <= count; ++k) {  // 枚举第 i 种题做 k 道
                    if (j >= k * marks) {  // 只有分数够时才可能做 k 道
                        f[i][j] = (f[i][j] + f[i - 1][j - k * marks]) % mod;  // 累加来自上一组题型的方案数并取模
                    }
                }
            }
        }
        return f[n][target];  // 所有题型都用上、恰好 target 分的方案数
    }
};