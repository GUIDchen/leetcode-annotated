// 题目：1118. 一月有多少天（Number of Days in a Month）
// 思路：先按公历闰年规则求出 leap，再用「下标即月份」的天数表直接查表返回当月天数。
// 时间复杂度：O(1)，只有一次闰年判断和一次下标访问；空间复杂度：O(1)，表长固定为 13。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfDays(int year, int month) {  // year：年份；month：1~12 的月份；返回该月天数
        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);  // 闰年规则：四年一闰、百年不闰、四百年再闰
        vector<int> days = {0, 31, leap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // 下标 0 占位不用，2 月按 leap 取 29 或 28
        return days[month];  // 月份天然比下标大 1，所以直接用它取表
    }  // 方法结束
};  // 类定义结束