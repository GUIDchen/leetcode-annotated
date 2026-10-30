# 题目：1118. 一月有多少天（Number of Days in a Month）
# 思路：先按公历闰年规则算出 leap，再用「下标即月份」的天数列表直接查表返回。
# 时间复杂度：O(1)，一次闰年判断加一次下标访问；空间复杂度：O(1)，列表长度固定为 13。
class Solution:  # LeetCode 约定的题解类
    def numberOfDays(self, year: int, month: int) -> int:  # year：年份；month：1~12 的月份；返回该月天数
        leap = (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)  # 闰年规则：四年一闰、百年不闰、四百年再闰
        days = [0, 31, 29 if leap else 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # 下标 0 占位不用，2 月按 leap 取 29 或 28
        return days[month]  # 月份比下标大 1，直接当下标用
