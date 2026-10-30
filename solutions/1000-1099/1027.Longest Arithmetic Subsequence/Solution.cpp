// 题目：1027. 最长等差数列（Longest Arithmetic Subsequence）
// 思路：动态规划。f[i][d + 500] 表示以 nums[i] 结尾、公差为 d 的等差数列长度；对每个 i 枚举更早的 k 做转移，公差范围 [-500, 500] 加 500 平移到非负下标。
// 时间复杂度：O(n^2)，枚举 (i, k) 数对；空间复杂度：O(n * 1001)，即二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestArithSeqLength(vector<int>& nums) {  // nums：输入数组；返回最长等差子序列的长度
        int n = nums.size();  // n 是数组长度
        int f[n][1001];  // DP 表：f[i][d] 表示以 nums[i] 结尾、公差为 d - 500 的最长等差数列长度
        memset(f, 0, sizeof(f));  // 全部清零（题意要求长度至少为 2 的转移才会计数，故初值 0 即可）
        int ans = 0;  // 记录过程中的最大长度
        for (int i = 1; i < n; ++i) {  // 枚举等差数列的最后一个元素下标 i
            for (int k = 0; k < i; ++k) {  // 枚举前一个元素下标 k（k < i）
                int j = nums[i] - nums[k] + 500;  // 计算公差并加 500 平移成非负下标，保证 0 <= j < 1001
                f[i][j] = max(f[i][j], f[k][j] + 1);  // 由以 k 结尾、同一公差的序列长度加一转移而来，取较大者
                ans = max(ans, f[i][j]);  // 用当前状态更新全局最大值
            }
        }
        // 上面统计的是「增加的边数」，序列长度还要再加上起点自身那一个元素
        return ans + 1;  // 长度 = 边数 + 1
    }
};