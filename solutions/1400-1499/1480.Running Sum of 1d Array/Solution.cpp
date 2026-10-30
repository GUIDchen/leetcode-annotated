// 题目：1480. 一维数组的动态和（Running Sum of 1d Array）
// 思路：原地前缀和，从第二个元素起把当前元素加上它的前一个元素，遍历结束后原数组就成了动态和。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，直接在原数组上修改（不计返回数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> runningSum(vector<int>& nums) {  // nums：输入数组，函数会就地改写
        for (int i = 1; i < nums.size(); ++i) nums[i] += nums[i - 1];  // 从下标 1 开始累加前一项，得到前缀和
        return nums;  // 原数组已被改写为动态和，直接返回
    }
};