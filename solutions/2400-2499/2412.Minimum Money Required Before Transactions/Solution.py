# 题目：2412. 完成所有交易的初始最少钱数（Minimum Money Required Before Transactions）
# 思路：先求所有亏损交易的钱坑总和 s，再枚举哪笔交易放在最后，取 s 加上该笔所需资金的最大值。
# 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumMoney(self, transactions: List[List[int]]) -> int:  # transactions 每项是 [花费, 回款]
        s = sum(max(0, a - b) for a, b in transactions)  # 所有亏损交易的净亏损之和，即必然要填的总钱坑
        ans = 0  # 记录所需的最小初始钱数
        for a, b in transactions:  # 枚举把哪一笔交易安排在最后完成
            if a > b:  # 亏损交易放最后：其他亏损的坑已计入 s，再准备本笔的起步资金
                ans = max(ans, s + b)  # 用该方案更新答案
            else:  # 盈利交易放最后：只需再备出本笔的花费
                ans = max(ans, s + a)  # 用该方案更新答案
        return ans  # 返回最小初始钱数
