// 题目：1029. 两地调度（Two City Scheduling）
// 思路：按「去 A 比去 B 便宜多少」排序，最划算去 A 的 n 人安排去 A，剩下 n 人去 B，交换任意两人都不会更优（贪心）。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int twoCitySchedCost(vector<vector<int>>& costs) {  // costs[i] = [去 A 城的费用, 去 B 城的费用]；返回安排 n 人去 A、n 人去 B 的最小总费用
        sort(costs.begin(), costs.end(), [](const vector<int>& a, const vector<int>& b) {  // 按「去 A 相对去 B 便宜多少」升序排序：a[0]-a[1] 越小，越应该去 A
            return a[0] - a[1] < b[0] - b[1];  // 排序比较器：差值小的排在前面
        });  // 排序结束，此时最该去 A 的 n 个人都排在前半段
        int n = costs.size() / 2;  // 人数是偶数，每座城市各去 n 人
        int ans = 0;  // 累计最小总费用
        for (int i = 0; i < n; ++i) {  // 前 n 人去 A，后 n 人去 B
            ans += costs[i][0] + costs[i + n][1];  // 第 i 个人去 A 的费用 + 第 i+n 个人去 B 的费用
        }  // 循环结束
        return ans;  // 返回最小总费用
    }  // 方法结束
};  // 类定义结束