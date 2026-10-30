// 题目：509. 斐波那契数（Fibonacci Number）
// 思路：滚动变量迭代，a 保持 F(k)、b 保持 F(k+1)，每次由两者相加推进一轮，循环 n 次后 a 就是 F(n)。
// 时间复杂度：O(n)；空间复杂度：O(1)，只用三个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int fib(int n) {  // n：要求第 n 个斐波那契数
        int a = 0, b = 1;  // a 保存 F(0)=0，b 保存 F(1)=1
        while (n--) {  // 迭代 n 次，每次把 (a, b) 往后推一项
            int c = a + b;  // 新的一项等于前两项之和
            a = b;  // a 向后移动一项
            b = c;  // b 向后移动一项
        }  // 循环结束，a 就是 F(n)
        return a;  // 返回答案
    }  // 方法结束
};  // 类定义结束