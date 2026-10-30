// 题目：2651. 计算列车到站时间（Calculate Delayed Arrival Time）
// 思路：计划到站时刻加上延误小时数，再对 24 取模，把可能跨天的时间折回 0..23。
// 时间复杂度：O(1)，一次加法与取模；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int findDelayedArrivalTime(int arrivalTime, int delayedTime) {  // arrivalTime：计划到站时刻（0..23 时）；delayedTime：延误的小时数
        return (arrivalTime + delayedTime) % 24;  // 相加后对 24 取模，跨天的时间自然折回 0..23
    }
};  // 类定义结束