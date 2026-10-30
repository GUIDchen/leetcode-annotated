// 题目：1085. 最小元素各数位之和（Sum of Digits in the Minimum Number）
// 思路：先找出数组最小值，再不断「取个位、除 10」求出它的数位和 s，最后判断 s 的奇偶：偶数返回 1，奇数返回 0。
// 时间复杂度：O(n + log x)，n 为数组长度，找最小值 O(n)、拆位 O(log x)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfDigits(vector<int>& nums) {  // nums 是给定的正整数数组
        int x = *min_element(nums.begin(), nums.end());  // 取整个数组的最小值（解引用最小元素迭代器）
        int s = 0;  // 累加最小值的各数位之和
        for (; x > 0; x /= 10) {  // 初始化已在上面完成；每轮把 x 去掉最低位，直到 x 变成 0
            s += x % 10;  // 取当前最低位的数字并累加
        }
        return s & 1 ^ 1;  // 运算符优先级：先 s&1 取奇偶，再 ^1 取反，即数位和为偶数返回 1、奇数返回 0
    }
};