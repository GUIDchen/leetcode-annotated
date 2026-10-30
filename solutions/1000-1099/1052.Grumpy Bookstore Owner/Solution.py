# 题目：1052. 爱生气的书店老板（Grumpy Bookstore Owner）
# 思路：固定收益是老板不生气时段的顾客数；再用长度 minutes 的滑动窗口统计生气时段被技巧覆盖的顾客数，取窗口和最大值。
# 时间复杂度：O(n)，一次滑动窗口扫描；空间复杂度：O(1)，只用常数个计数变量。
class Solution:  # LeetCode 约定的题解类
    def maxSatisfied(  # 参数跨行书写，返回最多满意的顾客数
        self, customers: List[int], grumpy: List[int], minutes: int  # customers 每分钟顾客数；grumpy 生气标记；minutes 可抑制生气的最长分钟数
    ) -> int:  # 函数签名结束
        mx = cnt = sum(c * g for c, g in zip(customers[:minutes], grumpy))  # cnt 是首个窗口内可挽回的顾客数，mx 同步记录其最大值
        for i in range(minutes, len(customers)):  # 窗口右移，每次进一个、出一个
            cnt += customers[i] * grumpy[i]  # 加入新进入窗口的那一分钟
            cnt -= customers[i - minutes] * grumpy[i - minutes]  # 减去移出窗口的那一分钟
            mx = max(mx, cnt)  # 维护窗口收益的最大值
        return sum(c * (g ^ 1) for c, g in zip(customers, grumpy)) + mx  # g ^ 1 取反求不生气时段的固定满意数，再加上技巧挽回的最大值
