// 题目：1822. 数组元素积的符号（Sign of the Product of an Array）
// 核心思路：乘积会溢出，所以只统计符号：遇到 0 直接返回 0，每遇到一个负数就把答案乘 -1 翻转符号。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int arraySign(vector<int>& nums) {  // nums 以引用传入，避免拷贝整个数组
        int ans = 1;  // ans 只记录符号，取值 1 或 -1
        for (int v : nums) {  // 范围 for：依次取出数组中的每个元素
            if (!v) return 0;  // 存在 0 时乘积为 0，提前返回
            if (v < 0) ans *= -1;  // 负数让符号翻转一次
        }
        return ans;  // 返回最终符号
    }
};  // 类定义结束