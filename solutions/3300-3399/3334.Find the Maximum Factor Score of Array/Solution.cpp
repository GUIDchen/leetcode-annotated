// 题目：3334. 数组的最大因子得分（Find the Maximum Factor Score of Array）
// 思路：预处理后缀 GCD/LCM，再从左往右维护前缀 GCD/LCM；枚举删除位置 i，用左前缀与右后缀的 GCD、LCM 相乘得到删除后的得分，同时考虑不删除的情形。
// 时间复杂度：O(n log V)，V 为元素最大值；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxScore(vector<int>& nums) {  // nums 是输入数组；返回删除至多一个元素后的最大因子得分
        int n = nums.size();  // 数组长度
        vector<long long> sufGcd(n + 1, 0);  // sufGcd[i]：nums[i..n-1] 的 GCD，多开一位便于处理空后缀
        vector<long long> sufLcm(n + 1, 1);  // sufLcm[i]：nums[i..n-1] 的 LCM，多开一位且初值为 1（空后缀的单位元）
        for (int i = n - 1; i >= 0; --i) {  // 从右往左预处理后缀
            sufGcd[i] = gcd(sufGcd[i + 1], nums[i]);  // 后缀 GCD：当前元素与右侧后缀的 GCD
            sufLcm[i] = lcm(sufLcm[i + 1], nums[i]);  // 后缀 LCM：当前元素与右侧后缀的 LCM
        }  // 后缀预处理结束

        long long ans = sufGcd[0] * sufLcm[0];  // 一个元素都不删时的得分，作为答案初值
        long long preGcd = 0, preLcm = 1;  // 前缀 GCD 初值 0、前缀 LCM 初值 1，分别是两种运算的单位元
        for (int i = 0; i < n; ++i) {  // 枚举被删除的元素位置 i
            ans = max(ans, gcd(preGcd, sufGcd[i + 1]) * lcm(preLcm, sufLcm[i + 1]));  // 删除 i 后，整体 GCD/LCM 由左前缀与右后缀合并得到
            preGcd = gcd(preGcd, nums[i]);  // 把 nums[i] 并入左前缀 GCD
            preLcm = lcm(preLcm, nums[i]);  // 把 nums[i] 并入左前缀 LCM
        }  // 枚举结束
        return ans;  // 返回最大得分
    }  // 方法结束
};  // 类定义结束
