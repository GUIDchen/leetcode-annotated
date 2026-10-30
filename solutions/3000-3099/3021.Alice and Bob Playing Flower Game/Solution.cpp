// 题目：3021. Alice 和 Bob 玩鲜花游戏（Alice and Bob Playing Flower Game）
// 思路：每回合共摘 x+y 朵花，Alice 后手获胜当且仅当 x+y 为奇数（奇数朵时 Bob 摘最后一朵后轮到 Alice，Alice 取最后一朵），即 x、y 一奇一偶；统计两段区间内奇数与偶数的个数后交叉相乘。
// 时间复杂度：O(1)，只有常数次四则运算；空间复杂度：O(1)，只用 4 个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long flowerGame(int n, int m) {  // n 是 x 的上界，m 是 y 的上界，返回 Alice 获胜的回合数
        long long a1 = (n + 1) / 2;  // a1：(n+1)/2 恰好是 1..n 中奇数的个数
        long long b1 = (m + 1) / 2;  // b1：(m+1)/2 恰好是 1..m 中奇数的个数
        long long a2 = n / 2;  // a2：1..n 中偶数的个数（除奇数外的部分）
        long long b2 = m / 2;  // b2：1..m 中偶数的个数
        return a1 * b2 + a2 * b1;  // x 奇 y 偶 与 x 偶 y 奇 两类组合之和，即 x+y 为奇数的方案数
    }  // 方法结束
};  // 题解类结束