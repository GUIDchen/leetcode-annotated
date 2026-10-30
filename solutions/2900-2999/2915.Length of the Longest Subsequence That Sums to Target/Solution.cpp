// 题目：2915. 和为目标值的最长子序列的长度（Length of the Longest Subsequence That Sums to Target）
// 思路：0/1 背包，f[i][j] 表示用前 i 个元素凑出和 j 的最长子序列长度，选与不选取较大值。
// 时间复杂度：O(n * target)；空间复杂度：O(n * target)，用二维表保存所有状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {  // nums 是候选元素，target 是目标和；返回和恰为 target 的最长子序列长度
        int n = nums.size();  // 元素个数
        int f[n + 1][target + 1];  // f[i][j]：只考虑前 i 个元素、和为 j 时的最长子序列长度（0/1 背包）
        memset(f, -0x3f, sizeof(f));  // 整个 DP 表先填一个足够小的负数，表示『这个和无法凑出』
        f[0][0] = 0;  // 边界：前 0 个元素凑出和 0 的空子序列，长度为 0
        for (int i = 1; i <= n; ++i) {  // 逐个考虑第 i 个元素（1-based）
            int x = nums[i - 1];  // 当前元素的值（下标要减 1）
            for (int j = 0; j <= target; ++j) {  // 枚举容量 j，这里容量就是目标和
                f[i][j] = f[i - 1][j];  // 不选当前元素：直接继承前 i-1 个元素的结果
                if (j >= x) {  // 选当前元素的前提是剩余容量 j - x 非负
                    f[i][j] = max(f[i][j], f[i - 1][j - x] + 1);  // 选当前元素后长度加 1，与不选的情况取较大值
                }
            }
        }
        return f[n][target] <= 0 ? -1 : f[n][target];  // 和凑不出来（仍是负的哨兵值）返回 -1，否则返回最长长度
    }
};