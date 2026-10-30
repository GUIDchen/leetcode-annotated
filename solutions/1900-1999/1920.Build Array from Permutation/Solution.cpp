// 题目：1920. 基于排列构建数组（Build Array from Permutation）
// 思路：按下标直接映射，遍历 nums 把 nums[num] 依次放入结果数组。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，为返回的结果数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> buildArray(vector<int>& nums) {  // nums 是 0~n-1 的排列，返回按 ans[i] = nums[nums[i]] 构造的新数组
        vector<int> ans;  // 结果数组，先为空再逐个追加
        for (int& num : nums) {  // 依次取出每个元素的值作为下标去查表
            ans.push_back(nums[num]);  // 按题意取 nums[num] 处的值追加到答案末尾
        }  // 结束遍历
        return ans;  // 返回构造好的数组
    }  // 方法结束
};  // 类定义结束