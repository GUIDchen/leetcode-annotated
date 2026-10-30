// 题目：1712. 将数组分成三个子数组的方案数（Ways to Split Array Into Three Subarrays）
// 思路：先求前缀和，枚举第一刀位置 i；数组非负所以前缀和单调，第二刀位置 j 的合法区间是一段连续下标，用 lower_bound 取下界、upper_bound 取上界，区间长度就是该 i 的方案数。
// 时间复杂度：O(n log n)，每个 i 做两次二分；空间复杂度：O(n)，前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 结果取模的常数

    int waysToSplit(vector<int>& nums) {  // nums 是非负整数数组，要切成三个非空连续子数组
        int n = nums.size();  // 数组长度
        vector<int> s(n, nums[0]);  // 前缀和数组：s[i] 表示 nums[0..i] 的和
        for (int i = 1; i < n; ++i) s[i] = s[i - 1] + nums[i];  // 递推求出每个位置的前缀和
        int ans = 0;  // 切分方案数
        for (int i = 0; i < n - 2; ++i) {  // 枚举第一刀位置 i，后面两段至少各留一个元素，故 i 最多到 n-3
            int j = lower_bound(s.begin() + i + 1, s.begin() + n - 1, s[i] << 1) - s.begin();  // 第二刀最早位置：使第二段和 s[j]-s[i] >= 第一段和 s[i]，即 s[j] >= 2*s[i]
            int k = upper_bound(s.begin() + j, s.begin() + n - 1, (s[n - 1] + s[i]) >> 1) - s.begin();  // 第二刀最晚位置的后一位：使第三段和 >= 第二段和，即 s[k] 不超过 (总和+s[i])/2 的位置都合法
            ans = (ans + k - j) % mod;  // [j, k) 内每个第二刀位置都合法，累加方案数并取模
        }  // 第一刀枚举结束
        return ans;  // 返回方案总数
    }  // 方法结束
};  // 类定义结束