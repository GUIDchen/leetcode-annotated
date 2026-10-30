// 题目：201. 数字范围按位与（Bitwise AND of Numbers Range）
// 思路：区间内所有数按位与等于它们的公共二进制前缀；不断用 right &= right - 1 抹掉 right 最低位的 1，直到 right 不超前于 left。
// 时间复杂度：O(log right)，最多循环 32 次；空间复杂度：O(1)，只用两个入参。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int rangeBitwiseAnd(int left, int right) {  // 求闭区间 [left, right] 内所有整数按位与的结果
        while (left < right) {  // right 仍大于 left，说明还有位需要抹掉
            right &= (right - 1);  // 抹掉 right 最低位的 1：range 内必然存在让该位变成 0 的数，所以答案里这一位一定是 0
        }
        return right;  // 此时 right 只剩公共前缀部分，正是区间按位与的答案
    }
};