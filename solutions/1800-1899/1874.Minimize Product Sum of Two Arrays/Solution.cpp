// 题目：1874. 两个数组的最小乘积和（Minimize Product Sum of Two Arrays）
// 思路：排序不等式——一个数组升序、另一个数组降序后逐位相乘再求和，即得到最小乘积和。
// 时间复杂度：O(n log n)，瓶颈是两次排序；空间复杂度：O(log n)，排序递归栈的额外开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minProductSum(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个等长数组
        ranges::sort(nums1);  // 第一个数组升序排列
        ranges::sort(nums2, greater<int>());  // 第二个数组降序排列
        int n = nums1.size();  // 数组长度
        int ans = 0;  // 乘积和的累加器
        for (int i = 0; i < n; ++i) {  // 逐位相乘
            ans += nums1[i] * nums2[i];  // 大值配小值，乘积和最小
        }  // 结束 for
        return ans;  // 返回最小乘积和
    }  // 结束方法
};  // 结束类
