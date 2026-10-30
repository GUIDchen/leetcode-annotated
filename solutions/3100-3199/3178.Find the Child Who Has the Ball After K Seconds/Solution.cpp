// 题目：3178. 找出 K 秒后拿着球的孩子（Find the Child Who Has the Ball After K Seconds）
// 思路：传球方向每 n-1 秒翻转一次，用除法把 k 拆成「完整周期数」和「周期内偏移量」，再按周期奇偶决定方向。
// 时间复杂度：O(1)，只做常数次算术运算；空间复杂度：O(1)，只用了几个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfChild(int n, int k) {  // n：孩子数量；k：经过的秒数
        int mod = k % (n - 1);  // 一个往返周期长度是 n-1 秒，mod 为周期内已经走过的偏移量
        k /= (n - 1);  // 整除得到走完了多少个完整周期，用于判断当前方向
        return k % 2 == 1 ? n - mod - 1 : mod;  // 奇数周期表示在回程，下标为 n-mod-1；偶数周期在去程，下标为 mod
    }
};