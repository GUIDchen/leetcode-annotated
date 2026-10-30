# 题目：2706. 购买两块巧克力（Buy Two Chocolates）
# 思路：先就地把价格升序排序，最便宜的两块之和就是最低花费；若超过 money 就一块也不买，原样返回 money。
# 时间复杂度：O(n log n)，排序是瓶颈；空间复杂度：O(1)，排序原地完成。
class Solution:  # LeetCode 约定的题解类
    def buyChoco(self, prices: List[int], money: int) -> int:  # prices 是各块巧克力的价格，money 是手里的钱
        prices.sort()  # 就地升序排序，最便宜的两块来到数组最前面
        cost = prices[0] + prices[1]  # 买两块巧克力的最低总花费
        return money if money < cost else money - cost  # 买不起就原样返回 money，买得起就返回找零后的钱
