// 题目：253. 会议室 II（Meeting Rooms II）
// 思路：差分数组。每场会议在开始时刻 +1、结束时刻 -1（结束时刻即释放房间），再做一次前缀和，峰值就是所需最少会议室数。
// 时间复杂度：O(n + m)，m 为最大的结束时间；空间复杂度：O(m)，差分数组的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 成员函数对外可见
    int minMeetingRooms(vector<vector<int>>& intervals) {  // intervals：每场会议的 [开始, 结束]，返回所需的最少会议室数量
        int m = 0;  // 记录最大的结束时间，用来确定差分数组的长度
        for (const auto& e : intervals) {  // 第一遍扫描：求最大结束时间
            m = max(m, e[1]);  // 更新最大值
        }  // 结束求最大值循环
        vector<int> d(m + 1);  // 差分数组：下标是时间点，值是该时间点房间数的增量
        for (const auto& e : intervals) {  // 逐场会议打差分标记
            d[e[0]]++;  // 开始时刻占用一间，增量 +1
            d[e[1]]--;  // 结束时刻释放，增量 -1（区间左闭右开，同一时刻释放的房间可立即复用）
        }  // 结束差分标记循环
        int ans = 0, s = 0;  // ans 记录峰值（最少房间数），s 是当前时刻同时在用的房间数
        for (int v : d) {  // 按时间顺序做前缀和
            s += v;  // 累加差分值，得到该时刻的占用数
            ans = max(ans, s);  // 更新占用峰值
        }  // 结束前缀和循环
        return ans;  // 峰值即为所需最少会议室数
    }  // 结束 minMeetingRooms 方法
};  // 结束 Solution 类
