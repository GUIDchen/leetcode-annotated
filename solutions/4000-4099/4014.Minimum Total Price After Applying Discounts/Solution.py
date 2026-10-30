# 题目：4014. 应用折扣后的最低总价（Minimum Total Price After Applying Discounts）
# 思路：价格与折扣都升序排序，然后用双指针分别从最贵的商品和最大的折扣开始反向配对——折扣是按比例的，大折扣用在贵商品上省得最多，剩余商品原价，该贪心最优。
# 时间复杂度：O(n log n + m log m)，主要开销是两次排序；空间复杂度：O(1)，只用常数个指针与累加变量。
class Solution:  # LeetCode 约定的题解类
    def minPrice(self, prices: list[int], discounts: list[int]) -> float:  # prices：每件商品的价格；discounts：可用的折扣百分比；返回所有商品最终价格之和的最小值
        prices.sort()  # 价格升序排序，便于从最贵的商品入手
        discounts.sort()  # 折扣升序排序，配合后面从末尾取最大折扣
        i, j = len(prices) - 1, len(discounts) - 1  # i 指向最贵的未处理商品，j 指向最大的未使用折扣
        ans = 0  # ans 累计最小总价（浮点，最终价格不四舍五入）
        while i >= 0 and j >= 0:  # 商品与折扣都还没用完时，把最大折扣用在最贵的商品上
            ans += prices[i] * (100 - discounts[j]) / 100  # 打 d% 折扣后的价格 = p * (100 - d) / 100，Python 的 / 本身就是浮点除法
            i -= 1  # 该商品处理完，指针前移
            j -= 1  # 该折扣已用掉，指针前移
        while i >= 0:  # 折扣用完，剩下的商品一律原价支付
            ans += prices[i]  # 原价计入总价
            i -= 1  # 处理下一个更便宜的商品
        return ans  # 返回所有商品最终价格之和的最小值
