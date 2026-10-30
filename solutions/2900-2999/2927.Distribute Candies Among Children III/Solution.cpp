// 题目：2927. 给小朋友们分糖果 III（Distribute Candies Among Children III）
// 思路：先按「隔板法」把 n 颗糖果分给 3 个小朋友（允许某人超限）的方案数记为 C(n+2, 2)，再用容斥减去至少一人超过 limit 的情况、加回至少两人超过 limit 的情况。
// 时间复杂度：O(1)，只做几次组合数运算；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long distributeCandies(int n, int limit) {  // n：糖果总数；limit：每个小朋友最多能拿到的颗数
        auto comb2 = [](int n) {  // 计算 C(n, 2) = n*(n-1)/2，即从 n 个中取 2 个的方案数
            return 1LL * n * (n - 1) / 2;  // 乘 1LL 提升为 64 位，防止 int 乘法溢出
        };
        if (n > 3 * limit) {  // 3 个小朋友最多只能分 3*limit 颗，超过就无解
            return 0;  // 没有任何合法方案
        }
        long long ans = comb2(n + 2);  // 隔板法：无上限时 x+y+z=n 的非负整数解个数是 C(n+2, 2)
        if (n > limit) {  // 有人可能拿到超过 limit 颗，用容斥把这些人扣掉
            ans -= 3 * comb2(n - limit + 1);  // 固定某一人超限（先扣掉 limit+1 颗），共 3 种选人方式
        }
        if (n - 2 >= 2 * limit) {  // 判断「两人同时超限」的交集是否非空
            ans += 3 * comb2(n - 2 * limit);  // 容斥加回被多减的部分：3 种两人同时超限的组合
        }
        return ans;  // 返回每个小朋友都不超过 limit 的方案数
    }
};