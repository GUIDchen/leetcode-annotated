// 题目：1414. 和为 K 的最少斐波那契数字数目（Find the Minimum Number of Fibonacci Numbers Whose Sum Is K）
// 思路：先生成不超过 k 的最大斐波那契数，再从大到小贪心：能减就减，减到 k 为 0。
// 时间复杂度：O(log k)，斐波那契数按指数增长，项数与递减次数都是 O(log k)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMinFibonacciNumbers(int k) {  // k 是目标和，返回求和为 k 所需的最少斐波那契数个数
        int a = 1, b = 1;  // 从最小的两个斐波那契数 1,1 出发
        while (b <= k) {  // 不断生成更大的斐波那契数，直到它超过 k
            int c = a + b;  // c 是 a、b 之后的下一个斐波那契数
            a = b;  // 两个数一起后移，a 变成 b 的前一项
            b = c;  // b 变成刚生成的项
        }  // 此时 b 是大于 k 的最小斐波那契数
        int ans = 0;  // 记录已选数字的个数
        while (k > 0) {  // k 还没被减完，继续用斐波那契数去凑
            if (k >= b) {  // 贪心：当前最大的斐波那契数 b 不超过 k 就取它
                k -= b;  // 从 k 中减去 b
                ++ans;  // 选中个数加一
            }  // 结束这一轮选择
            int c = b - a;  // 由 b = a + c 反推，c 是 b 的前一项、也就是新的 b
            b = a;  // b 回退到前一个斐波那契数
            a = c;  // a 回退到再前一个斐波那契数
        }  // 结束递减循环
        return ans;  // 返回最少数字个数
    }  // 结束题解方法
};  // 结束题解类