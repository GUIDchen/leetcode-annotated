# 题目：2929. 给小朋友们分糖果 II（Distribute Candies Among Children II）
# 思路：先用隔板法求出无上限时 x+y+z=n 的方案数 C(n+2, 2)，再用容斥减去至少一人超过 limit 的情况、加回至少两人超过 limit 的情况。
# 时间复杂度：O(1)，只做几次组合数运算；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def distributeCandies(self, n: int, limit: int) -> int:  # n：糖果总数；limit：每个小朋友最多能拿到的颗数
        if n > 3 * limit:  # 3 个小朋友最多只能分 3*limit 颗，超过就无解
            return 0  # 没有任何合法方案
        ans = comb(n + 2, 2)  # 隔板法：无上限时 x+y+z=n 的非负整数解个数是 C(n+2, 2)
        if n > limit:  # 有人可能拿到超过 limit 颗，需要容斥扣除
            ans -= 3 * comb(n - limit + 1, 2)  # 固定某一人超限（先扣掉 limit+1 颗），共 3 种选人方式
        if n - 2 >= 2 * limit:  # 判断「两人同时超限」的交集是否非空
            ans += 3 * comb(n - 2 * limit, 2)  # 容斥加回被多减的部分：3 种两人同时超限的组合
        return ans  # 返回每个小朋友都不超过 limit 的方案数
