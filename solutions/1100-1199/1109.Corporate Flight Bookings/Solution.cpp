// 题目：1109. 航班预订统计（Corporate Flight Bookings）
// 思路：差分数组。区间 [first, last] 加 seats 转化为 ans[first-1] += seats 与 ans[last] -= seats，最后做前缀和还原。
// 时间复杂度：O(n + m)，m 为预订条数，每个航班只累加一次；空间复杂度：O(n)，除返回数组外只用常数额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题接口
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {  // bookings 每项是 {first, last, seats}，n 是航班总数
        vector<int> ans(n);  // 差分数组，长度 n，默认全部为 0
        for (auto& e : bookings) {  // 逐条处理预订记录
            int first = e[0], last = e[1], seats = e[2];  // 拆出区间起点、终点与本次预订的座位数
            ans[first - 1] += seats;  // 差分：区间起点处加上 seats（航班号从 1 开始，故减一）
            if (last < n) {  // 右端点后面还有航班时才需要反向抵消
                ans[last] -= seats;  // 差分：右端点的下一个位置减去 seats，使区间之外不受影响
            }
        }
        for (int i = 1; i < n; ++i) {  // 对差分数组做前缀和，还原每个航班的真实预订数
            ans[i] += ans[i - 1];  // 当前位置累加上前一个位置的值
        }
        return ans;  // 返回航班 1..n 各自的预订总量
    }
};