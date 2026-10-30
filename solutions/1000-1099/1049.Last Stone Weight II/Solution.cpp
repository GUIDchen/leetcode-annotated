// 题目：1049. 最后一块石头的重量 II（Last Stone Weight II）
// 思路：问题等价于把石头分成两堆使重量差最小，转化为 0-1 背包：在容量 sum/2 内求能凑出的最大重量，答案为 sum - 2*背包值。
// 时间复杂度：O(m * sum)，m 为石头数；空间复杂度：O(m * sum)，使用二维 dp 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lastStoneWeightII(vector<int>& stones) {  // stones：石头重量；返回所有石头反复对撞后可能的最小剩余重量
        int s = accumulate(stones.begin(), stones.end(), 0);  // 总重量：分成两堆后答案就是两堆重量之差的绝对值
        int m = stones.size(), n = s >> 1;  // m 为物品数；n 为背包容量，取总和的一半向下取整
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));  // dp[i][j]：前 i 块石头中选出总重不超过 j 的最大可凑重量
        for (int i = 1; i <= m; ++i) {  // 逐个考虑每一块石头
            for (int j = 0; j <= n; ++j) {  // 枚举所有可能的背包容量
                dp[i][j] = dp[i - 1][j];  // 不选第 i 块石头时直接继承上一行
                if (stones[i - 1] <= j) dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);  // 选第 i 块石头：容量够则用它更新更优解
            }  // 容量枚举结束
        }  // 物品枚举结束
        return s - dp[m][n] * 2;  // 一堆重 dp[m][n]，另一堆重 s - dp[m][n]，相减即最小差值
    }  // 方法结束
};  // 题解类结束