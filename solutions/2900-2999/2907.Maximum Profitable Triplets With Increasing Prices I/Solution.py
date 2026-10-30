# 题目：2907. 价格递增的最大利润三元组 I（Maximum Profitable Triplets With Increasing Prices I）
# 核心思路：枚举中间下标 j，左侧取「价格更小者中的最大利润」，右侧取「价格更大者中的最大利润」，两侧都存在时用 left + profits[j] + right 更新答案。
# 时间复杂度：O(n^2)，每个 j 都扫描左右两侧；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, prices: List[int], profits: List[int]) -> int:  # prices 与 profits：价格数组和利润数组，返回最大利润和
        n = len(prices)  # 数组长度
        ans = -1  # -1 表示还没有找到任何合法三元组
        for j, x in enumerate(profits):  # 枚举中间下标 j，同时取出它对应的利润 x
            left = right = 0  # left/right 分别是左右两侧的最大利润，0 代表该侧还没找到
            for i in range(j):  # 在 j 左侧找一个价格更小、利润最大的元素
                if prices[i] < prices[j] and left < profits[i]:  # 价格严格小于 prices[j] 才能排在中间元素前面
                    left = profits[i]  # 前面条件已保证更大，所以直接赋值即可
            for k in range(j + 1, n):  # 在 j 右侧找价格更大、利润最大的元素
                if prices[j] < prices[k] and right < profits[k]:  # 价格严格大于 prices[j] 才能排在中间元素后面
                    right = profits[k]  # 同理直接更新右侧最大利润
            if left and right:  # 两侧都非 0 才说明三元组成立
                ans = max(ans, left + x + right)  # 左右最大利润加上中间利润更新答案
        return ans  # 没找到时 ans 仍然保持 -1
