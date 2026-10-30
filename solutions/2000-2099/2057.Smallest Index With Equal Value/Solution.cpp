// 题目：2057. 值相等的最小索引（Smallest Index With Equal Value）
// 思路：从左到右枚举下标 i，返回第一个满足 i % 10 == nums[i] 的下标；全都不满足则返回 -1。
// 时间复杂度：O(n)，最坏需要扫完整个数组；空间复杂度：O(1)，只用了一个循环变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestEqual(vector<int>& nums) {  // nums：输入数组；返回满足条件的最小下标
        for (int i = 0; i < nums.size(); ++i) {  // 从左往右枚举每个下标 i，保证先遇到的一定更小
            if (i % 10 == nums[i]) {  // 题目条件：下标对 10 取模的结果等于该位置的值
                return i;  // 第一个命中的下标就是最小下标，立即返回
            }
        }
        return -1;  // 扫完都没有命中，按题意返回 -1
    }
};
