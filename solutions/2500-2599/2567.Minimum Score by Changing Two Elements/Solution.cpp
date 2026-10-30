// 题目：2567. 修改两个元素的最小分数（Minimum Score by Changing Two Elements）
// 思路：先排序；改两个元素等价于「丢掉两个元素」，剩下的 n-2 个元素分数由最大值减最小值决定，枚举丢弃的三种位置组合取最小跨度。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(log n)，排序递归栈的额外开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizeSum(vector<int>& nums) {  // nums：允许修改两个元素的数组
        sort(nums.begin(), nums.end());  // 升序排序，使最小分数只取决于若干首尾元素
        int n = nums.size();  // 记录长度，避免下面重复调用 size()
        return min({nums[n - 1] - nums[2], nums[n - 2] - nums[1], nums[n - 3] - nums[0]});  // 三种丢弃方式：丢最小两个、各丢首尾一个、丢最大两个，取跨度最小者
    }
};