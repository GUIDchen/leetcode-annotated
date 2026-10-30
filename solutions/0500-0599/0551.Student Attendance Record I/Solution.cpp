// 题目：551. 学生出勤记录 I（Student Attendance Record I）
// 思路：题目要求同时满足「缺勤 A 少于 2 次」和「没有连续三次迟到 LLL」，于是用 count 统计 A 的个数、用 find 查找子串 LLL，两个条件相与即可。
// 时间复杂度：O(n)，一次计数加一次子串查找；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkRecord(string s) {  // s 只含 'A'（缺勤）、'L'（迟到）、'P'（到场），判断该记录是否满足获奖条件
        return count(s.begin(), s.end(), 'A') < 2 && s.find("LLL") == string::npos;  // 条件一：'A' 出现次数小于 2；条件二：找不到子串 "LLL"（npos 表示未找到），两个条件同时成立才返回 true
    }  // 类定义结束
};