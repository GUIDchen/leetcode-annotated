// 题目：1365. 有多少小于当前数字的数字（How Many Numbers Are Smaller Than the Current Number）
// 思路：复制并排序，对每个元素用 lower_bound 求它在有序数组中的首个位置，该下标正好等于比它小的元素个数。
// 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，副本数组 arr。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {  // nums：待统计的数组
        vector<int> arr = nums;  // 复制一份原数组，排序后用于二分查找
        sort(arr.begin(), arr.end());  // 升序排序副本
        for (int i = 0; i < nums.size(); ++i) {  // 逐个处理原数组中的每个位置
            nums[i] = lower_bound(arr.begin(), arr.end(), nums[i]) - arr.begin();  // lower_bound 找到首个不小于 nums[i] 的位置，其下标恰好等于比它小的元素个数
        }  // for 结束
        return nums;  // 返回统计好的数组
    }  // 方法结束
};  // 类定义结束