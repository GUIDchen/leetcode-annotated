// 题目：1904. 你完成的完整对局数（The Number of Full Rounds You Have Played）
// 思路：把时刻换算成分钟数，跨天时给结束时间加一天；完整对局数 = 结束前的整刻数 - 开始后的第一个整刻数（向上取整到 15 的倍数）。
// 时间复杂度：O(1)，只有常数次运算；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfRounds(string loginTime, string logoutTime) {  // loginTime / logoutTime：形如 HH:MM 的登录与登出时间
        auto f = [](string& s) {  // 局部 lambda：把 HH:MM 换算成从 00:00 起的分钟数
            int h, m;  // 分别保存解析出的小时与分钟
            sscanf(s.c_str(), "%d:%d", &h, &m);  // 按 HH:MM 的格式从字符串中解析出两个整数
            return h * 60 + m;  // 换算成当天的分钟数返回
        };  // lambda 结束
        int a = f(loginTime), b = f(logoutTime);  // 分别得到登录、登出的分钟数
        if (a > b) {  // 登录时间大于登出时间，说明跨过了午夜
            b += 1440;  // 给登出时间加一天的分钟数，让区间恢复成正常顺序
        }  // 结束 if 分支
        return max(0, b / 15 - (a + 14) / 15);  // b/15 是结束时刻之前的整刻数；(a+14)/15 让开始时刻向上取整到下一个 15 分钟刻度；两者相减再与 0 取大防止负数
    }  // 结束题解方法
};  // 结束题解类