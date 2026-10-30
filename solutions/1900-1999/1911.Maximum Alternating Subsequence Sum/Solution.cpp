// 题目：1911. 最大交替子序列和（Maximum Alternating Subsequence Sum）
// 思路：动态规划，g[i] 表示前 i 个数中最后取的元素作为「加号位」的最大交替和，f[i] 表示最后取的元素作为「减号位」的最大交替和，两者互相转移。
// 时间复杂度：O(n)，一次线性递推；空间复杂度：O(n)，两个长度为 n+1 的 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxAlternatingSum(vector<int>& nums) {  // nums：输入数组；和可能超出 int 范围，故返回 long long
        int n = nums.size();  // n：数组长度，DP 数组多开一位作为下标 0 的边界
        vector<long long> f(n + 1), g(n + 1);  // f：最后取的元素作「减号位」的最大和；g：最后取的元素作「加号位」的最大和，初值全 0 表示空序列
        for (int i = 1; i <= n; ++i) {  // 按下标 1..n 递推，nums 的下标相应为 i-1
            f[i] = max(g[i - 1] - nums[i - 1], f[i - 1]);  // 要么接在 g[i-1] 后面减掉当前数，要么跳过当前数沿用 f[i-1]
            g[i] = max(f[i - 1] + nums[i - 1], g[i - 1]);  // 要么接在 f[i-1] 后面加上当前数，要么跳过当前数沿用 g[i-1]
        }
        return max(f[n], g[n]);  // 两种结尾状态取较大值即为答案
    }  // 方法结束
};  // 类定义结束