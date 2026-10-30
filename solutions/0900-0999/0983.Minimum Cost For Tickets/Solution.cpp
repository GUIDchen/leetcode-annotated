// 题目：983. 最低票价（Minimum Cost For Tickets）
// 思路：记忆化 DFS，dfs(i) 表示覆盖 days[i..] 所有行程的最小花费；对三种票用 lower_bound 跳到票有效期结束后的第一个出行日，取三者最小。
// 时间复杂度：O(n log n)，每个状态做 3 次二分；空间复杂度：O(n)，记忆数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mincostTickets(vector<int>& days, vector<int>& costs) {  // days 是递增的出行日，costs 是三种票的价格
        int valid[3] = {1, 7, 30};  // 三种通行证分别覆盖 1 天、7 天、30 天
        int n = days.size();  // n 为出行日总数
        int f[n];  // 记忆数组，f[i] 表示从第 i 个出行日起的最小花费
        memset(f, 0, sizeof(f));  // 全部清零，0 代表该状态还没计算过
        function<int(int)> dfs = [&](int i) {  // 递归 lambda：处理从第 i 个出行日开始的行程
            if (i >= n) {  // 所有出行日都已覆盖
                return 0;  // 不再需要买票
            }  // 递归出口结束
            if (f[i]) {  // 该状态已经计算过
                return f[i];  // 直接返回记忆值，避免重复搜索
            }  // 记忆命中分支结束
            f[i] = INT_MAX;  // 先置为无穷大，便于后面取最小值
            for (int k = 0; k < 3; ++k) {  // 枚举三种票
                int j = lower_bound(days.begin(), days.end(), days[i] + valid[k]) - days.begin();  // lower_bound 找到被该票覆盖完后第一个仍未覆盖的出行日下标
                f[i] = min(f[i], dfs(j) + costs[k]);  // 三种买法取最小花费
            }  // 票种循环结束
            return f[i];  // 返回并把结果记忆下来
        };  // lambda 定义结束
        return dfs(0);  // 从第一个出行日开始计算
    }  // 方法结束
};  // 类定义结束