// 题目：2413. 最小偶倍数（Smallest Even Multiple）
// 思路：偶数 n 的最小偶倍数就是 n 自己；奇数 n 的最小偶倍数是 2*n，用三目运算符一次判断即可。
// 时间复杂度：O(1)，一次取模加一次乘法；空间复杂度：O(1)，不额外占用内存。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestEvenMultiple(int n) {  // n 是给定的正整数，返回它的最小正偶倍数
        return n % 2 == 0 ? n : n * 2;  // n 为偶数时返回 n，否则返回 n*2
    }  // 方法定义结束
};  // 类定义结束