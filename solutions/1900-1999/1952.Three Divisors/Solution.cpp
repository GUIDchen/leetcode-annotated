// 题目：1952. 三除数（Three Divisors）
// 思路：除 1 和 n 本身外，2..n-1 中恰好有 1 个数能整除 n 时，n 的除数总数正好是 3。
// 时间复杂度：O(n)，一次线性枚举；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isThree(int n) {  // n：待判断的正整数
        int cnt = 0;  // 统计 2..n-1 之间能整除 n 的数的个数
        for (int i = 2; i < n; ++i) {  // 枚举所有可能的真除数
            cnt += n % i == 0;  // 能整除时布尔值转成 1 累加
        }
        return cnt == 1;  // 真除数恰有 1 个，加上 1 和 n 本身正好 3 个除数
    }
};  // LeetCode 题解类结束