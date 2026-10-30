// 题目：494. 目标和（Target Sum）
// 思路：给每个数加 + / - 号，等价于选出和为 (s - target) / 2 的「负号子集」，于是转成 0-1 背包计数：f[i][j] 表示前 i 个数凑出和 j 的方案数。
// 时间复杂度：O(n·s)，n 为元素个数、s 为总和的半量级；空间复杂度：O(n·s)，DP 二维表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findTargetSumWays(vector<int>& nums, int target) {  // nums：非负整数数组；target：目标值；返回使正负号和为 target 的方案数
        int s = accumulate(nums.begin(), nums.end(), 0);  // s 为数组元素总和（accumulate 用 0 作为初值，返回 int）
        if (s < target || (s - target) % 2) {  // 全取负号都凑不到 target，或 s - target 为奇数（无法整除 2），都无解
            return 0;  // 这两种情况方案数为 0
        }  // 参数非法分支结束
        int m = nums.size();  // 物品个数
        int n = (s - target) / 2;  // 需要凑出的「负号子集」目标和：(s - target) / 2
        int f[m + 1][n + 1];  // f[i][j]：前 i 个数中选出若干使和为 j 的方案数（变长二维数组）
        memset(f, 0, sizeof(f));  // 把 DP 表清零（memset 按字节置 0，对 int 的 0 是正确的）
        f[0][0] = 1;  // 边界：不选任何数凑出和 0，视为 1 种方案
        for (int i = 1; i <= m; ++i) {  // 逐个物品（前 i 个数）推进
            for (int j = 0; j <= n; ++j) {  // 枚举当前凑出的和 j
                f[i][j] = f[i - 1][j];  // 不选第 i 个数：方案数继承前 i - 1 个数的结果
                if (j >= nums[i - 1]) {  // 第 i 个数的值不超过 j 时，才可能选它
                    f[i][j] += f[i - 1][j - nums[i - 1]];  // 选第 i 个数：累加前 i - 1 个数凑出 j - nums[i-1] 的方案数
                }  // 选与不选两种转移结束
            }  // 枚举 j 结束
        }  // 枚举 i 结束
        return f[m][n];  // 前 m 个数恰好凑出 n 的方案数即答案
    }  // 方法结束
};  // 类定义结束