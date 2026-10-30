// 题目：70. 爬楼梯（Climbing Stairs）
// 思路：设 f(i) 为爬到第 i 阶的方法数，则 f(i) = f(i-1) + f(i-2)（最后一步迈 1 阶或 2 阶）；用两个滚动变量把空间压到常数。
// 时间复杂度：O(n)，一次线性递推；空间复杂度：O(1)，只保留相邻两项。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int climbStairs(int n) {  // n：楼梯总阶数
        int a = 0, b = 1;  // a 保存 f(i-2)、b 保存 f(i-1)，初值对应 f(0)=0、f(1)=1
        for (int i = 0; i < n; ++i) {  // 递推 n 次，把 f(1) 一直推到 f(n)
            int c = a + b;  // c 就是当前的 f(i) = f(i-2) + f(i-1)
            a = b;  // 为下一轮准备：a 前移成 f(i-1)
            b = c;  // 为下一轮准备：b 前移成 f(i)
        }
        return b;  // 循环结束后 b 正好是 f(n)
    }
};