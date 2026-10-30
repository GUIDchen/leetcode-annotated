# 题目：2431. 最大限度地提高购买水果的口味（Maximize Total Tastiness of Purchased Fruits）
# 思路：记忆化搜索，dfs(i, j, k) 表示从第 i 个水果开始、剩余预算 j、剩余优惠券 k 时能取得的最大口味值。
# 时间复杂度：O(n * maxAmount * maxCoupons)；空间复杂度：O(n * maxAmount * maxCoupons)，用于缓存各状态结果。
class Solution:  # LeetCode 约定的题解类
    def maxTastiness(  # price：各水果价格；tastiness：各水果口味值；maxAmount：预算；maxCoupons：优惠券张数
        self, price: List[int], tastiness: List[int], maxAmount: int, maxCoupons: int  # 形参列表换行书写，语义不变
    ) -> int:  # 返回能买到的最大口味总和
        @cache  # 装饰器：按参数组合缓存 dfs 的返回值，避免同一状态重复计算
        def dfs(i, j, k):  # i：当前水果下标；j：剩余预算；k：剩余优惠券张数
            if i == len(price):  # 所有水果都已决策完
                return 0  # 没有水果可买，收益为 0
            ans = dfs(i + 1, j, k)  # 方案一：跳过第 i 个水果，预算与券都不变
            if j >= price[i]:  # 剩余预算够付原价
                ans = max(ans, dfs(i + 1, j - price[i], k) + tastiness[i])  # 方案二：原价买下，扣掉价格并累加口味值
            if j >= price[i] // 2 and k:  # 预算够付半价且还有优惠券可用
                ans = max(ans, dfs(i + 1, j - price[i] // 2, k - 1) + tastiness[i])  # 方案三：用一张券半价买，券数减一
            return ans  # 返回当前状态的最优口味值

        return dfs(0, maxAmount, maxCoupons)  # 从第 0 个水果、满预算、满优惠券开始搜索
