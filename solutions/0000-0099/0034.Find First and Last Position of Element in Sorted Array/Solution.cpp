// 题目：34. 在排序数组中查找元素的第一个和最后一个位置（Find First and Last Position of Element in Sorted Array）
// 思路：数组升序，用两次 lower_bound：一次求 target 首次出现的位置 l，一次求 target+1 首次出现的位置 r，则 [l, r-1] 就是全部 target。
// 时间复杂度：O(log n)，两次二分；空间复杂度：O(1)，只用了常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> searchRange(vector<int>& nums, int target) {  // nums 是升序数组，target 是目标值；返回 [起点, 终点]，不存在时返回 [-1, -1]
        int l = lower_bound(nums.begin(), nums.end(), target) - nums.begin();  // lower_bound 返回第一个 ≥ target 的元素迭代器，减去 begin() 转成下标 l，即第一个 target 的位置
        int r = lower_bound(nums.begin(), nums.end(), target + 1) - nums.begin();  // 再求第一个 ≥ target+1 的位置 r，等价于第一个 > target 的位置；用 target+1 是为了跨过所有重复的 target
        if (l == r) {  // l == r 说明区间里一个 target 都没有
            return {-1, -1};  // 按题目约定返回 [-1, -1]
        }  // if 分支结束
        return {l, r - 1};  // r 是第一个大于 target 的位置，所以 r-1 正是最后一个 target 的下标
    }  // 方法结束
};  // 类定义结束
