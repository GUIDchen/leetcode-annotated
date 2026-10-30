// 题目：628. 三个数的最大乘积（Maximum Product of Three Numbers）
// 思路：排序后只需比较两种组合：「最大的三个数」与「最大数乘最小的两个负数」。
// 时间复杂度：O(n log n)，排序开销；空间复杂度：O(log n)，排序所需的递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumProduct(vector<int>& nums) {  // nums 是整数数组，要求选三个数使乘积最大
        sort(nums.begin(), nums.end());  // 升序排序，方便直接取两端的元素
        int n = nums.size();  // 记录数组长度，后面按下标取数要用
        int a = nums[n - 1] * nums[n - 2] * nums[n - 3];  // 方案一：最大的三个数相乘（全正或全负时最优）
        int b = nums[n - 1] * nums[0] * nums[1];  // 方案二：最大数乘最小的两个负数，两个负号相乘得正
        return max(a, b);  // 两种方案取较大者即为答案
    }
};