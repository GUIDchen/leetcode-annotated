# 题目：1360. 日期之间隔几天（Number of Days Between Two Dates）
# 思路：把每个日期换算成「自 1971-01-01 起算的天数」——累加整年天数、整月天数再补上当月天数，两日期相减取绝对值。
# 时间复杂度：O(Y + 12)，Y 为年份跨度（本题很小）；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def daysBetweenDates(self, date1: str, date2: str) -> int:  # 求两个 YYYY-MM-DD 日期之间相差的天数
        def isLeapYear(year: int) -> bool:  # 判断是否为闰年
            return year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)  # 四年一闰；整百年要能被 400 整除才是闰年

        def daysInMonth(year: int, month: int) -> int:  # 返回某年某月的天数
            days = [  # 平年各月天数的查表数组，2 月先按 28 天算
                31,  # 1 月：31 天
                28 + int(isLeapYear(year)),  # 2 月：平年 28 天，闰年 29 天（bool 转 0/1 后相加）
                31,  # 3 月：31 天
                30,  # 4 月：30 天
                31,  # 5 月：31 天
                30,  # 6 月：30 天
                31,  # 7 月：31 天
                31,  # 8 月：31 天
                30,  # 9 月：30 天
                31,  # 10 月：31 天
                30,  # 11 月：30 天
                31,  # 12 月：31 天
            ]  # 天数表结束
            return days[month - 1]  # 下标 month-1 即该月天数

        def calcDays(date: str) -> int:  # 把日期换算成自 1971-01-01 起算的天数（基准可任意，只要两个日期一致）
            year, month, day = map(int, date.split("-"))  # 按 '-' 切分后一次性取出年、月、日
            days = 0  # 累计天数
            for y in range(1971, year):  # 累加 1971 年到 year-1 年每一整年的天数
                days += 365 + int(isLeapYear(y))  # 平年 365 天，闰年多 1 天
            for m in range(1, month):  # 累加今年 1 月到 month-1 月每一整月的天数
                days += daysInMonth(year, m)  # 该月天数由 daysInMonth 给出，已考虑闰年
            days += day  # 最后补上当月的第 day 天
            return days  # 返回绝对天数

        return abs(calcDays(date1) - calcDays(date2))  # 两个绝对天数相减取绝对值，就是两个日期之间的间隔
