// 题目：3986. Number of Elapsed Seconds Between Two Times（3986. 统计起止时间经过的秒数）
// 核心思路：把 HH:MM:SS 换算成从 00:00:00 起的当天总秒数（时×3600 + 分×60 + 秒），结束时刻与开始时刻的秒数相减即为经过的秒数。
// 复杂度：时间 O(1)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公开接口
    int secondsBetweenTimes(string startTime, string endTime) {  // 返回从 startTime 到 endTime 经过的秒数
        return f(endTime) - f(startTime);  // 两个时刻的当天秒数直接相减
    }  // 方法结束

private:  // 内部辅助函数
    int f(const string& s) {  // 把 HH:MM:SS 字符串换算成当天的总秒数
        return stoi(s.substr(0, 2)) * 3600  // 小时位 substr(0, 2) 乘以 3600 换算为秒
            + stoi(s.substr(3, 2)) * 60  // 分钟位 substr(3, 2) 乘以 60 换算为秒
            + stoi(s.substr(6));  // 秒位 substr(6) 原样相加
    }  // 辅助函数结束
};  // 类定义结束