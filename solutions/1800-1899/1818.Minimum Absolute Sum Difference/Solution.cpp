// 题目：1818. 绝对差值和（Minimum Absolute Sum Difference）
// 思路：先算原始绝对差总和 s；把 nums1 排序后，对每个位置二分查找最接近 nums2[i] 的值，求出该位置能减少的最大差值 mx，答案为 (s - mx) mod 1e9+7。
// 时间复杂度：O(n log n)，排序与 n 次二分；空间复杂度：O(n)，保存 nums1 的排序副本。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个等长数组
        const int mod = 1e9 + 7;  // 题目要求的取模值
        vector<int> nums(nums1);  // 复制一份 nums1 用于排序，避免破坏原数组
        sort(nums.begin(), nums.end());  // 升序排序，为后续二分查找做准备
        int s = 0, n = nums.size();  // s：原始绝对差总和；n：数组长度
        for (int i = 0; i < n; ++i) {  // 逐位累加原始绝对差
            s = (s + abs(nums1[i] - nums2[i])) % mod;  // 加上 |nums1[i] - nums2[i]| 并取模
        }
        int mx = 0;  // 记录替换某一个元素后绝对差可能减少的最大值
        for (int i = 0; i < n; ++i) {  // 枚举被替换的位置 i
            int d1 = abs(nums1[i] - nums2[i]);  // 该位置当前的绝对差
            int d2 = 1 << 30;  // 替换后能达到的最小绝对差，初始化为足够大的值
            int j = lower_bound(nums.begin(), nums.end(), nums2[i]) - nums.begin();  // 二分找第一个 >= nums2[i] 的下标
            if (j < n) {  // 存在右侧候选值 nums[j]
                d2 = min(d2, abs(nums[j] - nums2[i]));  // 用右侧较近的值更新最小绝对差
            }
            if (j) {  // 存在左侧候选值 nums[j-1]
                d2 = min(d2, abs(nums[j - 1] - nums2[i]));  // 用左侧较近的值更新最小绝对差
            }
            mx = max(mx, d1 - d2);  // 该位置替换后能减少的差值，取全局最大
        }
        return (s - mx + mod) % mod;  // 总和减去最大可减少量，加 mod 防止出现负数
    }
};  // 结束 Solution 类定义