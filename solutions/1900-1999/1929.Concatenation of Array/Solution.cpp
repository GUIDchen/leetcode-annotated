// 题目：1929. 数组串联（Concatenation of Array）
// 思路：直接在原数组尾部追加一份自身，push_back 期间 nums 的长度在增长，因此循环上界必须提前用 n 固定。
// 时间复杂度：O(n)，追加 n 次；空间复杂度：O(n)，扩容后数组长度为 2n。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getConcatenation(vector<int>& nums) {  // nums：原数组，原地追加后返回
        for (int i = 0, n = nums.size(); i < n; ++i) {  // n 提前固定为原始长度，避免跟着 push_back 一起变长
            nums.push_back(nums[i]);  // 把第 i 个元素追加到末尾，得到首尾相接的效果
        }
        return nums;  // 返回长度为 2n 的数组
    }
};