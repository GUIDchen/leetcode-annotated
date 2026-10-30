# 题目：551. 学生出勤记录 I（Student Attendance Record I）
# 思路：题目要求同时满足「缺勤 A 少于 2 次」和「没有连续三次迟到 LLL」，用 count 统计 A、用 in 判断子串 LLL，两个条件相与即可。
# 时间复杂度：O(n)，一次计数加一次子串查找；空间复杂度：O(1)，只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def checkRecord(self, s: str) -> bool:  # s 只含 'A'（缺勤）、'L'（迟到）、'P'（到场），判断该记录是否满足获奖条件
        return s.count('A') < 2 and 'LLL' not in s  # 缺勤次数小于 2，且字符串中不存在子串 'LLL'（即没有连续三次迟到）
