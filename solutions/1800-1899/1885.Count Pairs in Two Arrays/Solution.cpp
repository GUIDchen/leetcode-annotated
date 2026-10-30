// 题目：1885. 统计数对（Count Pairs in Two Arrays）
// 思路：把 nums1[i]+nums1[j] > nums2[i]+nums2[j] 化为差值数组上的 nums[i]+nums[j] > 0，排序后用左右双指针统计合法数对。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，需要额外保存差值数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countPairs(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 是两个等长数组
        int n = nums1.size();  // 数组长度
        vector<int> nums(n);  // 存放每个下标上的差值 nums1[i] - nums2[i]
        for (int i = 0; i < n; ++i) {  // 逐个下标计算差值
            nums[i] = nums1[i] - nums2[i];  // 两数相加后比较，等价于比较两边差值之和是否大于 0
        }
        ranges::sort(nums);  // 升序排序，使差值单调，方便双指针
        int l = 0, r = n - 1;  // 左右指针，分别指向差值的两端
        long long ans = 0;  // 答案用 long long，数对数量可能超过 int
        while (l < r) {  // 固定右端点，找满足条件的最左端点
            while (l < r && nums[l] + nums[r] <= 0) {  // 两数之和不够大就把左端点右移
                ++l;  // 丢弃更小的值
            }
            ans += r - l;  // 区间 [l, r-1] 内的每个下标都能与 r 组成合法数对
            --r;  // 右端点左移，处理下一组
        }
        return ans;  // 返回满足条件的数对总数
    }
};
