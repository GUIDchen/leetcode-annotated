// 题目：401. 二进制手表（Binary Watch）
// 思路：暴力枚举。小时只有 0-11、分钟只有 0-59 共 720 种组合，统计小时与分钟的二进制中 1 的个数之和，等于 turnedOn 的就是合法时刻。
// 时间复杂度：O(1)，固定枚举 12*60 个时刻；空间复杂度：O(1)，除答案数组外只用常数空间。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    vector<string> readBinaryWatch(int turnedOn) {  // 返回所有恰好点亮 turnedOn 个 LED 的时刻
        vector<string> ans;  // 存放结果的字符串数组
        for (int i = 0; i < 12; ++i) {  // 枚举小时：二进制手表的小时只有 0 到 11
            for (int j = 0; j < 60; ++j) {  // 枚举分钟：0 到 59
                if (__builtin_popcount(i) + __builtin_popcount(j) == turnedOn) {  // __builtin_popcount 统计二进制中 1 的个数，两段之和就是亮灯总数
                    ans.push_back(to_string(i) + ":" + (j < 10 ? "0" : "") + to_string(j));  // 分钟不足两位时左边补 0，再拼成 H:MM 格式存入答案
                }
            }
        }
        return ans;  // 返回所有合法时刻
    }
};  // 题解类结束