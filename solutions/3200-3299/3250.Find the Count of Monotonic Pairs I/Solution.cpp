// 题目：3250. 单调数组对的数目 I（Find the Count of Monotonic Pairs I）
// 思路：动态规划，f[i][j] 表示 arr1[i]=j 的方案数；由 arr1 不降、arr2 不升推出上一位取值的上界，再用前缀和加速转移。
// 时间复杂度：O(n·m)，n 为数组长度、m 为数组最大值；空间复杂度：O(n·m)，用于存放 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countOfPairs(vector<int>& nums) {  // nums：输入数组；返回满足条件的单调数组对数目
        const int mod = 1e9 + 7;  // 取模常量，防止答案溢出
        int n = nums.size();  // n：数组长度
        int m = *max_element(nums.begin(), nums.end());  // m：数组最大值，作为 arr1 各元素取值的上界
        vector<vector<int>> f(n, vector<int>(m + 1));  // f[i][j]：arr1[i]=j 时的方案数，初值全为 0
        for (int j = 0; j <= nums[0]; ++j) {  // 第 0 位：arr1[0] 可以是 0..nums[0] 中任意一个值
            f[0][j] = 1;  // 每种取值只对应一种分法，方案数为 1
        }
        vector<int> g(m + 1);  // g：f[i-1] 的前缀和，用于 O(1) 求一段下标区间的方案和
        for (int i = 1; i < n; ++i) {  // 从左到右逐位确定 arr1 的取值
            g[0] = f[i - 1][0];  // 前缀和的第 0 项先单独赋值
            for (int j = 1; j <= m; ++j) {  // 递推整个前缀和数组
                g[j] = (g[j - 1] + f[i - 1][j]) % mod;  // 累加并取模：g[j]=f[i-1][0]+...+f[i-1][j]
            }
            for (int j = 0; j <= nums[i]; ++j) {  // 枚举 arr1[i] 的取值 j，需满足 arr1[i]+arr2[i]=nums[i]
                int k = min(j, j + nums[i - 1] - nums[i]);  // 上一位取值的上界：既要 arr1 不降(k<=j)，又要 arr2 不升(k<=j+nums[i-1]-nums[i])
                if (k >= 0) {  // k<0 表示不存在合法的上一位取值，该状态无解
                    f[i][j] = g[k];  // 所有合法的 f[i-1][0..k] 求和即为 f[i][j]
                }
            }
        }
        int ans = 0;  // ans：累计所有合法末位取值的方案数
        for (int j = 0; j <= nums[n - 1]; ++j) {  // 最后一位 arr1[n-1] 可以取 0..nums[n-1]
            ans = (ans + f[n - 1][j]) % mod;  // 逐项累加并取模
        }
        return ans;  // 返回总方案数
    }
};
