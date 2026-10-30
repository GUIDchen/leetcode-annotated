// 题目：3925. 连接逆序数组（Concatenate Array With Reverse）
// 思路：开一个长度为 2n 的答案数组，一次遍历同时填好两半：前 n 位照抄 nums，后 n 位把 nums 倒序写入。
// 时间复杂度：O(n)，只遍历一遍；空间复杂度：O(n)，答案数组本身占 2n 个位置。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> concatWithReverse(vector<int>& nums) {  // nums：原数组，返回长度为 2n 的拼接结果
        int n = nums.size();  // 原数组长度
        vector<int> ans(2 * n);  // 答案数组长度为 2n
        for (int i = 0; i < n; ++i) {  // 一次遍历同时填前后两半
            ans[i] = nums[i];  // 前 n 位原样复制 nums
            ans[i + n] = nums[n - i - 1];  // 后 n 位按倒序填入
        }  // 遍历结束
        return ans;  // 返回拼接结果
    }  // 方法结束
};  // 类定义结束
