// 题目：1267. 统计参与通信的服务器（Count Servers that Communicate）
// 思路：先统计每行、每列各有多少台服务器；再遍历每台服务器，只要它所在行或列还有别的服务器，它就能参与通信，计数即可。
// 时间复杂度：O(mn)，两次遍历网格；空间复杂度：O(m+n)，行、列计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countServers(vector<vector<int>>& grid) {  // grid 中 grid[i][j] == 1 表示该格有服务器，0 表示空
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        vector<int> row(m), col(n);  // row[i] 记录第 i 行的服务器数，col[j] 记录第 j 列的服务器数
        for (int i = 0; i < m; ++i) {  // 逐行统计
            for (int j = 0; j < n; ++j) {  // 逐列统计
                row[i] += grid[i][j];  // 把当前格贡献加到所在行的计数里
                col[j] += grid[i][j];  // 把当前格贡献加到所在列的计数里
            }  // 结束列循环
        }  // 结束行循环
        int ans = 0;  // ans 记录能参与通信的服务器台数
        for (int i = 0; i < m; ++i) {  // 第二遍遍历所有格子
            for (int j = 0; j < n; ++j) {  // 逐列检查
                ans += grid[i][j] && (row[i] > 1 || col[j] > 1);  // 该格有服务器且同行或同列还有别的服务器时，布尔值转成 1 累加
            }  // 结束列循环
        }  // 结束行循环
        return ans;  // 返回可通信的服务器总数
    }  // 结束 countServers
};  // 结束题解类
