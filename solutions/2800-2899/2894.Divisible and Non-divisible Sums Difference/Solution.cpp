// 题目：2894. 分类求和并作差（Divisible and Non-divisible Sums Difference）
// 思路：一次遍历 1..n，能被 m 整除的数取负号、不能被整除的数取正号，累加即得 num1 - num2。
// 时间复杂度：O(n)，只遍历 1 到 n 一次；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int differenceOfSums(int n, int m) {  // n：上界；m：除数
        int ans = 0;  // 累加答案，初始为 0
        for (int i = 1; i <= n; ++i) {  // 枚举 1..n 的每个整数
            ans += i % m ? i : -i;  // 不能被 m 整除时加 i，能被整除时减 i
        }  // 返回 num1 - num2
        return ans;
    }
};