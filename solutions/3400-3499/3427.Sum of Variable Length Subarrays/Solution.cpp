// 3427. Sum of Variable Length Subarrays / 3427. 变长子数组求和
// 核心思路：前缀和预处理，以 i 结尾的子数组和等于 s[i + 1] - s[max(0, i - nums[i])]。
// 复杂度：时间 O(n)，空间 O(n)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    int subarraySum(vector<int>& nums) {  // nums 为 0 起始下标的整数数组，返回所有变长子数组的元素和之和
        int n = nums.size();  // 数组长度 n
        vector<int> s(n + 1);  // 前缀和数组 s，s[i] 表示 nums 前 i 个元素之和，多开一位省去越界判断
        for (int i = 1; i <= n; ++i) {  // 从 1 开始递推前缀和
            s[i] = s[i - 1] + nums[i - 1];  // s[i] = s[i - 1] + nums[i - 1]，即把 nums[0..i-1] 的和存进 s[i]
        }  // 前缀和预处理结束
        int ans = 0;  // 累加所有变长子数组之和
        for (int i = 0; i < n; ++i) {  // 枚举每个右端点 i
            ans += s[i + 1] - s[max(0, i - nums[i])];  // 以 i 结尾、长度 nums[i] + 1 的子数组左端点下界为 max(0, i - nums[i])，区间和由前缀和作差得到
        }  // 右端点枚举结束
        return ans;  // 返回所有子数组和之和
    }  // 方法结束
};  // 类定义结束
