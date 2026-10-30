// 题目：2089. 找出数组排序后的目标下标（Find Target Indices After Sorting Array）
// 思路：把数组升序排序后，所有等于 target 的元素一定连续出现，直接顺序扫描并收集它们的下标即可，结果天然升序。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(1)（不计返回数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> targetIndices(vector<int>& nums, int target) {  // nums：待排序数组；target：目标值；返回所有等于 target 的下标（升序）
        sort(nums.begin(), nums.end());  // 先升序排序，让相同的值聚集到一起
        vector<int> ans;  // 存放答案下标的动态数组
        for (int i = 0; i < nums.size(); ++i) {  // 排序后从头到尾扫描每个位置
            if (nums[i] == target) {  // 当前元素等于目标值
                ans.push_back(i);  // 把它的下标加入答案
            }  // if 分支结束
        }  // for 循环结束
        return ans;  // 返回全部目标下标
    }  // 结束 targetIndices 方法
};  // 结束 Solution 类