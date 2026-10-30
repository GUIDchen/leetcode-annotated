# 题目：1491. 去掉最低工资和最高工资后的工资平均值（Average Salary Excluding the Minimum and Maximum Salary）
# 思路：用内置 sum/min/max 一次拿到总和与最值，再从总和中扣掉最值，除以 n-2。
# 时间复杂度：O(n)，sum/min/max 各扫一遍；空间复杂度：O(1)，只存一个中间和。
class Solution:  # LeetCode 约定的题解类
    def average(self, salary: List[int]) -> float:  # 返回去掉一个最小值和一个最大值后的平均值
        s = sum(salary) - min(salary) - max(salary)  # 总和减去最小值与最大值，剩下的就是参与平均的部分
        return s / (len(salary) - 2)  # 除以 n-2；Python 的 / 天然返回浮点数，不需要额外转换
