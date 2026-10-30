// 题目：172. 阶乘后的零（Factorial Trailing Zeroes）
// 思路：末尾的零来自因子 10 = 2 × 5，而 2 的数量远多于 5，所以只需统计 1..n 中因子 5 的总个数：n/5 + n/25 + n/125 + …。
// 时间复杂度：O(log₅n)，n 每次除以 5；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int trailingZeroes(int n) {  // 计算 n! 末尾连续零的个数
        int ans = 0;  // 记录因子 5 的总个数
        while (n) {  // 反复除以 5，直到 n 变成 0
            n /= 5;  // 这一层贡献 floor(n/5) 个因子 5（覆盖 5、25、125 … 的倍数）
            ans += n;  // 把这一层的个数累加进答案
        }  // 循环结束
        return ans;  // 返回因子 5 的总数，也就是末尾零的个数
    }  // 方法结束
};  // 类定义结束