// 题目：3789. 采购的最小花费（Minimum Cost to Acquire Required Items）
// 核心思路：只有三种买法——两类需求各自单买、全部用双类型物品覆盖、先买 min(need1,need2) 个双类型物品再补单买；分别算出代价后取最小值。
// 复杂度：时间 O(1)，三次乘法与求最小值；空间 O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // public 区的方法供判题器调用
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {  // 给定两类单买价格、双类型价格与两类需求量，求满足全部需求的最小总花费
        long long a = 1LL * need1 * cost1 + 1LL * need2 * cost2;  // 方案一：两类需求分别单买
        long long b = 1LL * costBoth * max(need1, need2);  // 方案二：全部用双类型物品覆盖，数量取两类需求的最大值
        int mn = min(need1, need2);  // 两类需求中较小的那个，即可配对的双类型物品数量上限
        long long c = 1LL * costBoth * mn  // 方案三：先买 mn 个双类型物品，剩余缺口再分别单买
            + 1LL * (need1 - mn) * cost1  // 双类型物品的费用，加上类型 1 缺口的单买费用
            + 1LL * (need2 - mn) * cost2;  // 再加上类型 2 缺口的单买费用
        return min({a, b, c});  // 三种方案取最小值
    }  // 方法结束
};  // 类定义结束
