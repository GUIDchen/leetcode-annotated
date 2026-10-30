# 题目：1185. 一周中的第几天（Day of the Week）
# 思路：直接调用标准库 datetime 构造日期对象，再用 strftime('%A') 取出英文星期全名，不用自己算闰年与偏移。
# 时间复杂度：O(1)，日期构造与格式化都是常数操作；空间复杂度：O(1)，只额外保存一个日期对象。
class Solution:  # LeetCode 约定的题解类
    def dayOfTheWeek(self, day: int, month: int, year: int) -> str:  # day/month/year 依次是日、月、年，题目保证是 1971~2100 年间的合法日期
        return datetime.date(year, month, day).strftime('%A')  # 构造 date 对象后按 %A 格式化，得到 'Sunday' ~ 'Saturday' 这样的完整英文名
