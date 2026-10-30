// 题目：1150. 检查一个数是否在数组中占绝大多数（Check If a Number Is Majority Element in a Sorted Array）
// 思路：数组升序，用两次二分分别求出 target 的起始与结束位置，出现次数严格大于 n/2 即为绝大多数。
// 时间复杂度：O(log n)，两次二分查找；空间复杂度：O(1)，只用两个迭代器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isMajorityElement(vector<int>& nums, int target) {  // nums 升序，target 是要检查的数
        auto left = lower_bound(nums.begin(), nums.end(), target);  // 第一个等于 target 的位置
        auto right = upper_bound(nums.begin(), nums.end(), target);  // 第一个大于 target 的位置
        return right - left > nums.size() / 2;  // 区间长度就是 target 的出现次数，严格超过一半才是绝大多数
    }  // 方法结束
};  // 类定义结束