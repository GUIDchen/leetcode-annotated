// 题目：1913. 两个数对之间的最大乘积差（Maximum Product Difference Between Two Pairs）
// 思路：排序后最大两个数之积减去最小两个数之积，即为最大的乘积差。
// 时间复杂度：O(n log n)，来自一次排序；空间复杂度：O(log n)，排序所需栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProductDifference(vector<int>& nums) {  // nums：输入数组，至少 4 个正数
        sort(nums.begin(), nums.end());  // 升序排序，最大值在后两个、最小值在前两个
        int n = nums.size();  // n：数组长度，用来定位末尾两个下标
        return nums[n - 1] * nums[n - 2] - nums[0] * nums[1];  // 最大两个数之积减去最小两个数之积
    }  // 方法结束
};  // 类定义结束