// 题目：2409. 统计共同度过的日子数（Count Days Spent Together）
// 思路：把 MM-DD 格式的日期换算成当年的第几天，两人的共同区间就是两个区间的交集，交集天数为 max(0, end - start + 1)。
// 时间复杂度：O(1)，只有常数次字符串与下标操作；空间复杂度：O(1)，只用一张 12 个月的前缀和表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    static constexpr int f[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};  // 前缀和：f[i] 表示第 i 个月之前累计的天数（按平年计算）

    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {  // 四个参数分别是两人各自的到达日与离开日，格式为 MM-DD
        string start = max(arriveAlice, arriveBob);  // 日期是定长字符串，字典序比较等价于日期比较，较大者是较晚的到达日
        string end = min(leaveAlice, leaveBob);  // 较小者是较早的离开日，两者构成交集区间
        int d1 = f[stoi(start.substr(0, 2)) - 1] + stoi(start.substr(3));  // 把开始日期换算成当年的第几天
        int d2 = f[stoi(end.substr(0, 2)) - 1] + stoi(end.substr(3));  // 把结束日期换算成当年的第几天
        return max(d2 - d1 + 1, 0);  // 交集长度即共同天数，区间不相交时取 0
    }  // 方法结束
};  // Solution 定义结束