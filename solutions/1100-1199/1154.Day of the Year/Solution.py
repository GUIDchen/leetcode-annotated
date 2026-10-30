# 题目：1154. 一年中的第几天（Day of the Year）
# 思路：解析出年、月、日，按闰年规则确定二月天数，累加前面各月的天数再加上当月第几天 d。
# 时间复杂度：O(1)，月份最多遍历 11 项；空间复杂度：O(1)，只用固定长度的天数列表。
class Solution:  # LeetCode 约定的题解类
    def dayOfYear(self, date: str) -> int:  # date 形如 YYYY-MM-DD
        y, m, d = (int(s) for s in date.split('-'))  # 按 - 切分后转成整数，得到年、月、日
        v = 29 if y % 400 == 0 or (y % 4 == 0 and y % 100) else 28  # 闰年时二月 29 天，否则 28 天
        days = [31, v, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # 十二个月的天数表，二月用 v 填充
        return sum(days[: m - 1]) + d  # 前 m-1 个整月天数之和 加上 当月第几天 d
