# 题目：2070. 每一个查询的最大美丽值（Most Beautiful Item for Each Query）
# 思路：物品按价格排序，再把查询按价格排序（保留原下标）；离线从小到大回答查询，用物品指针纳入价格不超过查询的物品，并维护最大美丽值。
# 时间复杂度：O((n + m) log(n + m))，两次排序主导；空间复杂度：O(m)，用于答案数组与排序后的查询序列。
class Solution:  # LeetCode 约定的题解类
    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:  # items 为 (价格, 美丽值)，queries 为查询价格；返回每个查询的最大美丽值
        items.sort()  # 按价格升序排序，价格相同时按美丽值升序
        n, m = len(items), len(queries)  # n 为物品数，m 为查询数
        ans = [0] * len(queries)  # 预分配答案数组，长度与查询数相同
        i = mx = 0  # i 是物品指针，mx 是已纳入物品的最大美丽值
        for q, j in sorted(zip(queries, range(m))):  # 把查询按价格升序排列，同时保留它原来的下标 j
            while i < n and items[i][0] <= q:  # 把价格不超过本次查询 q 的物品全部纳入考虑
                mx = max(mx, items[i][1])  # 更新已纳入物品的最大美丽值
                i += 1  # 物品指针后移，每个物品只纳入一次
            ans[j] = mx  # 当前查询的答案写回它原来的位置
        return ans  # 返回按原查询顺序排列的答案
