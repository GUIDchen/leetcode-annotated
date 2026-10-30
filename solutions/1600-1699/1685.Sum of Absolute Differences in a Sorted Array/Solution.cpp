// 题目：1685. 有序数组中差绝对值之和（Sum of Absolute Differences in a Sorted Array）
// 思路：前缀和 + 一次遍历。nums 已有序，对第 i 个元素，左侧 i 个都比它小、右侧 n-i-1 个都比它大，于是两段绝对值之和可以用总和 s 与当前前缀和 t 直接算出，无需逐个相减。
// 时间复杂度：O(n)，每个位置 O(1) 计算；空间复杂度：O(1)，除返回数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {  // nums：递增有序数组；返回每个位置与其余元素的差的绝对值之和
        int s = accumulate(nums.begin(), nums.end(), 0), t = 0;  // s 是数组总和，t 是当前元素之前的前缀和（初始为 0）
        int n = nums.size();  // n 是数组长度
        vector<int> ans(n);  // ans 存放每个下标对应的答案
        for (int i = 0; i < n; ++i) {  // 从左到右遍历，同时维护前缀和 t
            int v = nums[i] * i - t + s - t - nums[i] * (n - i);  // 左侧 i 个元素贡献 nums[i]*i - t；右侧含自身 n-i 个元素贡献 (s - t) - nums[i]*(n - i)，两者相加即为答案
            ans[i] = v;  // 写入当前下标的答案
            t += nums[i];  // 把当前元素累加进前缀和，供下一个位置使用
        }
        return ans;  // 返回所有位置的结果
    }
};  // 题解类结束