// 题目：3082. 求出所有子序列的能量和（Find the Sum of the Power of All Subsequences）
// 思路：背包计数 DP，f[i][j] 表示前 i 个数中被标记出的子序列和为 j 的方案数；不选第 i 个数时方案数翻倍，选它则由 j - nums[i-1] 转移。
// 时间复杂度：O(n·k)；空间复杂度：O(n·k)，滚动数组可降到 O(k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfPower(vector<int>& nums, int k) {  // nums：原数组；k：目标和；返回所有子序列的能量和（模 1e9+7）
        const int mod = 1e9 + 7;  // 取模常量
        int n = nums.size();  // 数组长度
        int f[n + 1][k + 1];  // f[i][j]：前 i 个元素中，被标记出的子序列和为 j 的方案数
        memset(f, 0, sizeof(f));  // 初始化为 0
        f[0][0] = 1;  // 空集和为 0，方案数为 1
        for (int i = 1; i <= n; ++i) {  // 逐个考虑第 i 个元素（即 nums[i-1]）
            for (int j = 0; j <= k; ++j) {  // 枚举被标记子序列的和 j
                f[i][j] = (f[i - 1][j] * 2) % mod;  // 不选第 i 个元素：和不变，而它可自由地不被标记，所以方案数翻倍
                if (j >= nums[i - 1]) {  // 和足够大时才可能选上第 i 个元素
                    f[i][j] = (f[i][j] + f[i - 1][j - nums[i - 1]]) % mod;  // 选第 i 个元素：累加「和减少 nums[i-1]」的方案数
                }
            }
        }
        return f[n][k];  // 前 n 个元素中和为 k 的方案数即为答案
    }
};
