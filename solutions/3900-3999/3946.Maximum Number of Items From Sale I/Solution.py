# 题目：3946. 购买最多物品数目 I（Maximum Number of Items From Sale I）
# 思路：先算出买每个商品能白得多少件（factor 是它倍数的都算），做 0-1 背包求花 j 元的最大物品数；剩余预算按最低单价反复购买。
# 复杂度：时间 O(n^2 + n * budget)，空间 O(budget)。
class Solution:  # LeetCode 约定的题解类
    def maximumSaleItems(self, items: List[List[int]], budget: int) -> int:  # items[i] = [factor, price]；budget 是总预算
        f = [0] * (budget + 1)  # 0-1 背包：f[j] 表示花掉 j 元预算最多能换到的物品数
        mn = inf  # mn 记录所有商品中的最低单价
        for factor, price in items:  # 逐个商品考虑「买下它」
            mn = min(mn, price)  # 更新最低单价
            cnt = sum(factor_j % factor == 0 for factor_j, _ in items)  # cnt：买下该商品后一次性可得的物品数（factor 是它倍数的都算）
            for j in range(budget, price - 1, -1):  # 逆序枚举预算，保证每件商品最多选一次
                f[j] = max(f[j], f[j - price] + cnt)  # 不买 vs 买下，取物品数更大的方案
        return max(x + (budget - i) // mn for i, x in enumerate(f))  # 枚举已花掉的预算 i，剩余部分按最低单价继续买，取最大
