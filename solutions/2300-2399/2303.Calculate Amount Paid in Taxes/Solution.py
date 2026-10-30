# 题目：2303. 计算应缴税款总额（Calculate Amount Paid in Taxes）
# 思路：按分档区间逐档累加，每档应税额 = max(0, min(收入, 本档上界) - 上一档上界)，乘以该档百分比，最后除以 100。
# 时间复杂度：O(n)，n 为档数，只遍历一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def calculateTax(self, brackets: List[List[int]], income: int) -> float:  # brackets：按上界递增的分档 [上界, 百分比]；income：总收入
        ans = prev = 0  # ans 累计税款的最小单位数值，prev 记录上一档的上界
        for upper, percent in brackets:  # 按顺序逐档处理收入区间，同时取出上界与百分比
            ans += max(0, min(income, upper) - prev) * percent  # 落在本档内的收入 = min(income, upper) - prev，max(0, ...) 处理收入没到本档的情况
            prev = upper  # 把本档上界记为下一档的起点
        return ans / 100  # 除以 100，把按百分比累加的数值换算成实际税款
