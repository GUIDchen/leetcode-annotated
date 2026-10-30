// 题目：1360. 日期之间隔几天（Number of Days Between Two Dates）
// 思路：把每个日期换算成「距 1970-12-31 的天数」——累加整年天数、整月天数再补上当月天数，两个日期相减取绝对值即可。
// 时间复杂度：O(Y + 12)，Y 为年份跨度（本题很小）；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 下列辅助方法对外可见
    int daysBetweenDates(string date1, string date2) {  // 求两个 YYYY-MM-DD 日期之间相差的天数
        return abs(calcDays(date1) - calcDays(date2));  // 分别换算成绝对天数后相减，取绝对值得到间隔
    }  // daysBetweenDates 结束

    bool isLeapYear(int year) {  // 判断某年是否为闰年
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);  // 四年一闰；但整百年要能被 400 整除才是闰年
    }  // isLeapYear 结束

    int daysInMonth(int year, int month) {  // 返回某年某月的天数
        int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // 平年各月天数的查表数组，2 月先按 28 天算
        days[1] += isLeapYear(year);  // 闰年时 2 月加一天；bool 参与算术会自动转成 0/1
        return days[month - 1];  // 下标 month-1 即该月天数
    }  // daysInMonth 结束

    int calcDays(string date) {  // 把日期换算成自 1971-01-01 起算的天数（基准可任意，只要两个日期一致）
        int year = stoi(date.substr(0, 4));  // 取年份：前 4 个字符
        int month = stoi(date.substr(5, 2));  // 取月份：从下标 5 开始 2 个字符，跳过 '-'
        int day = stoi(date.substr(8, 2));  // 取日：从下标 8 开始 2 个字符
        int days = 0;  // 累计天数
        for (int y = 1971; y < year; ++y) {  // 累加 1971 年到 year-1 年每一整年的天数
            days += 365 + isLeapYear(y);  // 平年 365 天，闰年多 1 天
        }  // 整年累加结束
        for (int m = 1; m < month; ++m) {  // 累加今年 1 月到 month-1 月每一整月的天数
            days += daysInMonth(year, m);  // 该月天数由 daysInMonth 给出，已考虑闰年
        }  // 整月累加结束
        days += day;  // 最后补上当月的第 day 天
        return days;  // 返回绝对天数
    }  // calcDays 结束
};  // 类定义结束