// 题目：1137. 第 N 个泰波那契数（N-th Tribonacci Number）
// 思路：三项滚动的迭代：只用 a、b、c 三个变量保存最近三项，循环 n 次把窗口整体前移。
// 时间复杂度：O(n)；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int tribonacci(int n) {  // 求第 n 个泰波那契数 T(n) = T(n-1) + T(n-2) + T(n-3)，初值 T(0)=0、T(1)=1、T(2)=1
        long long a = 0, b = 1, c = 1;  // 三个变量滚动保存最近三项，用 long long 防止中间结果溢出
        while (n--) {  // 循环 n 次：n-- 先判断再自减，循环结束时 a 恰好是 T(n)
            long long d = a + b + c;  // 先算出下一项（当前三项之和）暂存到 d
            a = b;  // 窗口前移：a 变成原来的 b
            b = c;  // b 变成原来的 c
            c = d;  // c 变成刚刚算出的新项 d
        }  // 循环结束
        return (int) a;  // a 就是第 n 项，转回 int 返回（结果不超过 2^31-1）
    }  // 方法结束
};  // 类定义结束