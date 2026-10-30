# 3687. 图书馆逾期罚款计算器 / Library Late Fee Calculator
# 核心思路：按逾期天数分段计费（1 天 1 元、2 到 5 天每天 2 元、超过 5 天每天 3 元），累加每本书的罚款
# 时间复杂度 O(n)，空间复杂度 O(1)
class Solution:  # 题解类
    def lateFee(self, daysLate: List[int]) -> int:  # 返回所有书籍的逾期罚款总额
        def f(x: int) -> int:  # 内部函数：计算单本书逾期 x 天的罚款
            if x == 1:  # 只逾期 1 天
                return 1  # 罚款 1 元
            if x > 5:  # 逾期超过 5 天
                return 3 * x  # 每天 3 元
            return 2 * x  # 逾期 2 到 5 天，每天 2 元

        return sum(f(x) for x in daysLate)  # 累加所有书籍的罚款
