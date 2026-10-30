# 题目：3789. 采购的最小花费（Minimum Cost to Acquire Required Items）
# 核心思路：枚举三种买法——两类需求各自单买、全部用双类型物品覆盖、先买 min(need1,need2) 个双类型物品再补单买，取三者代价的最小值。
# 复杂度：时间 O(1)，三次乘法与求最小值；空间 O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(  # 给定两类单买价格、双类型价格与两类需求量，求满足全部需求的最小总花费
        self, cost1: int, cost2: int, costBoth: int, need1: int, need2: int  # 参数续行：两类单买价格、双类型价格与两类需求量
    ) -> int:  # 参数续行结尾，声明返回最小总花费
        a = need1 * cost1 + need2 * cost2  # 方案一：两类需求分别单买
        b = costBoth * max(need1, need2)  # 方案二：全部用双类型物品覆盖，数量取两类需求的最大值
        mn = min(need1, need2)  # 两类需求中较小的那个，即可配对的双类型物品数量上限
        c = costBoth * mn + (need1 - mn) * cost1 + (need2 - mn) * cost2  # 方案三：先买 mn 个双类型物品，剩余缺口分别单买
        return min(a, b, c)  # 三种方案取最小值
