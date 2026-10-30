// 3774. 最大和最小 K 个元素的绝对差 / Absolute Difference Between Maximum and Minimum K Elements
// 核心思路：排序后最大的 k 个元素位于数组右端、最小的 k 个元素位于左端，逐位相减并累加即得两组之和的绝对差。
// 复杂度：时间复杂度 O(n log n)，空间复杂度 O(log n)，其中 n 为数组长度（含排序递归栈开销）。
class Solution {  // 定义题解类
public:  // 公有成员
    int absDifference(vector<int>& nums, int k) {  // 返回最大 k 个元素之和与最小 k 个元素之和的绝对差
        ranges::sort(nums);  // 升序排序，让最值分别落在数组两端
        int n = nums.size();  // 数组长度
        int ans = 0;  // 累计最大 k 个与最小 k 个元素之差
        for (int i = 0; i < k; ++i) {  // 同时取第 i 大与第 i 小的元素
            ans += nums[n - i - 1] - nums[i];  // 累加第 i 大元素与第 i 小元素之差
        }  // k 对元素处理完毕
        return ans;  // 返回绝对差
    }  // 方法结束
};  // 类定义结束
