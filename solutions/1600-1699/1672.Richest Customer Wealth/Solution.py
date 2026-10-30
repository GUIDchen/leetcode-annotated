# 题目：1672. 最富有客户的资产总量（Richest Customer Wealth）
# 思路：每行是一位客户的账户列表，对每行求和后取最大值。
# 时间复杂度：O(m·n)，每个数字只累加一次；空间复杂度：O(1)，生成器表达式逐个产出，不额外建表。
class Solution:  # LeetCode 约定的题解类
    def maximumWealth(self, accounts: List[List[int]]) -> int:  # accounts 的每一行是一位客户的资产清单
        return max(sum(v) for v in accounts)  # 生成器表达式逐行求和，max 取其中的最大值
