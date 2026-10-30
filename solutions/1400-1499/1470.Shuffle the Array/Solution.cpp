// 题目：1470. 重新排列数组（Shuffle the Array）
// 核心思路：依次把 nums[i] 与 nums[i + n] 成对压入结果数组。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，新建长度为 2n 的结果数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> shuffle(vector<int>& nums, int n) {  // nums 长度为 2n，n 为每半段的长度
        vector<int> ans;  // 结果数组
        for (int i = 0; i < n; ++i) {  // 遍历前半段的下标
            ans.push_back(nums[i]);  // 先放前半段的第 i 个元素
            ans.push_back(nums[i + n]);  // 再放后半段对应的第 i 个元素
        }  // 循环体结束
        return ans;  // 返回重新排列后的数组
    }  // 方法结束
};  // 类定义结束