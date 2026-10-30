// 题目：312. 戳气球（Burst Balloons）
// 思路：区间 DP。两端补虚拟气球 1，f[i][j] 表示只打爆开区间 (i,j) 内气球的最大金币，枚举最后被打爆的 k 划分左右子问题。
// 时间复杂度：O(n³)，三层枚举所有区间与分界点；空间复杂度：O(n²)，DP 二维表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxCoins(vector<int>& nums) {  // nums：每个气球上的数字
        int n = nums.size();  // 气球个数
        vector<int> arr(n + 2, 1);  // 两侧各补一个值为 1 的虚拟气球，省去边界判断
        for (int i = 0; i < n; ++i) {  // 把原数组搬到下标 1..n
            arr[i + 1] = nums[i];  // 偏移一位，使 arr[0] 与 arr[n+1] 始终是虚拟气球
        }

        vector<vector<int>> f(n + 2, vector<int>(n + 2, 0));  // f[i][j]：只打爆开区间 (i,j) 内气球能得到的最大金币
        for (int i = n - 1; i >= 0; --i) {  // 从右往左枚举左端点，保证求 f[i][j] 时更窄的区间已经算好
            for (int j = i + 2; j <= n + 1; ++j) {  // 右端点至少比左端点大 2，开区间内才有气球
                for (int k = i + 1; k < j; ++k) {  // 枚举区间内最后被打爆的气球 k
                    f[i][j] = max(f[i][j], f[i][k] + f[k][j] + arr[i] * arr[k] * arr[j]);  // k 最后爆：左右子区间最优解相加，再加上 k 与边界 i、j 的乘积
                }
            }
        }
        return f[0][n + 1];  // 答案是整个区间 (0, n+1) 的最大金币
    }
};