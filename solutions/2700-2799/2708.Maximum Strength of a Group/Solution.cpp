// 题目：2708. 一个小组的最大实力值（Maximum Strength of a Group）
// 思路：n 不超过 13，直接用位掩码枚举所有非空子集，逐个累乘并记录最大乘积。
// 时间复杂度：O(2^n · n)，共 2^n - 1 个子集、每个子集扫 n 位；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxStrength(vector<int>& nums) {  // nums：可供选择的元素，长度不超过 13
        long long ans = -1e14;  // 答案初值取足够小的负数，保证任何子集的乘积都能更新它
        int n = nums.size();  // 元素个数，也决定子集枚举的上限
        for (int i = 1; i < 1 << n; ++i) {  // 用位掩码 i 枚举所有非空子集（从 1 开始，跳过空集）
            long long t = 1;  // 当前子集的乘积，从乘法单位元 1 开始
            for (int j = 0; j < n; ++j) {  // 逐位检查第 j 个元素是否被选入当前子集
                if (i >> j & 1) {  // 第 j 位为 1，说明 nums[j] 属于当前子集
                    t *= nums[j];  // 把 nums[j] 乘进当前子集的乘积
                }
            }
            ans = max(ans, t);  // 用当前子集的乘积更新全局最大实力值
        }
        return ans;  // 所有非空子集乘积中的最大值
    }
};