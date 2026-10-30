// 题目：2396. 严格回文的数字（Strictly Palindromic Number）
// 思路：n 在 n-2 进制下恒为 "11" 是回文，但总能在某个 2..n-2 的进制下写成非回文形式，故这样的数不存在，直接返回 false。
// 时间复杂度：O(1)，只是常量次操作；空间复杂度：O(1)，不使用额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isStrictlyPalindromic(int n) {  // n：待判断的整数（按结论无需真正计算，但保留参数以匹配题面签名）
        return false;  // 严格回文的数字不存在，任何 n 都返回 false
    }
};