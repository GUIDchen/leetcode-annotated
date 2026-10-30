// 题目：4010. 数对的最大强度（Maximize Pair Strength Using GCD）
// 思路：直接枚举所有数对 (i, j)，强度为两数乘积除以 gcd 的平方，边枚举边取最大值；乘积用 64 位整数以免溢出。
// 时间复杂度：O(n^2 log V)，每对都要求一次 gcd；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxPairStrength(vector<int>& nums) {  // nums：数对从这里选取；返回所有数对中的最大强度
        int n = nums.size();  // n 为数组长度
        long long ans = 0;  // ans 记录当前找到的最大强度

        for (int i = 0; i < n; i++) {  // 枚举数对中的第一个元素
            for (int j = i + 1; j < n; j++) {  // 枚举数对中的第二个元素，只向后取以避免重复
                long long g = gcd(nums[i], nums[j]);  // 两数的最大公约数
                long long x = 1LL * nums[i] * nums[j] / (g * g);  // 强度 = 两数乘积 / gcd 的平方；1LL 提前把运算提升为 long long 防溢出
                ans = max(ans, x);  // 更新最大强度
            }  // 结束第二个元素的枚举
        }  // 结束第一个元素的枚举

        return ans;  // 返回最大强度
    }  // 结束 maxPairStrength
};  // 结束 Solution 类