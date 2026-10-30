// 题目：1503. 所有蚂蚁掉下来前的最后一刻（Last Moment Before All Ants Fall Out of a Plank）
// 思路：两只蚂蚁相遇掉头等价于彼此穿过继续走，所以只需比较最靠右的左行蚂蚁与最靠左的右行蚂蚁谁更晚落地。
// 时间复杂度：O(L + R)，两个列表各扫一遍；空间复杂度：O(1)，只用一个变量记录答案。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {  // n：木板右端点（坐标为 0..n）；left：向左走的蚂蚁位置；right：向右走的蚂蚁位置
        int ans = 0;  // 记录所有蚂蚁中最晚落地的时刻，初值为 0
        for (int& x : left) {  // 遍历向左走的蚂蚁
            ans = max(ans, x);  // 位置 x 的左行蚂蚁要花 x 时间到达 0 端落地
        }
        for (int& x : right) {  // 遍历向右走的蚂蚁
            ans = max(ans, n - x);  // 位置 x 的右行蚂蚁要花 n - x 时间到达 n 端落地
        }
        return ans;  // 两类时间取最大，就是全部蚂蚁掉落的最后时刻
    }
};