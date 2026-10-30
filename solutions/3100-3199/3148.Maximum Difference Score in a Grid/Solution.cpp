// 题目：3148. 矩阵中的最大得分（Maximum Difference Score in a Grid）
// 思路：路径只能向右或向下，得分等价于「终点值 - 左上方某个格子的值」；用 f[i][j] 维护左上矩形内的最小值，ans 取 max(grid[i][j] - 该最小值)。
// 时间复杂度：O(mn)，整张矩阵只遍历一次；空间复杂度：O(mn)，保存前缀最小值表 f。
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {  // grid：输入矩阵
        int m = grid.size(), n = grid[0].size();  // m、n：矩阵的行数与列数
        const int inf = 1 << 30;  // inf：表示「不存在」的极大值
        int ans = -inf;  // ans：最大得分，初值取负的极大值
        int f[m][n];  // f[i][j]：以 (i,j) 为右下角的前缀矩形中的最小值
        for (int i = 0; i < m; ++i) {  // 逐行遍历
            for (int j = 0; j < n; ++j) {  // 逐列遍历
                int mi = inf;  // mi：左上方可作为起点的最小格子值（(0,0) 处仍是 inf，表示没有起点）
                if (i) {  // 上方格子存在
                    mi = min(mi, f[i - 1][j]);  // 用上方的前缀最小值更新 mi
                }
                if (j) {  // 左方格子存在
                    mi = min(mi, f[i][j - 1]);  // 用左方的前缀最小值更新 mi
                }
                ans = max(ans, grid[i][j] - mi);  // 当前值减去起点最小值，就是一条合法路径的得分
                f[i][j] = min(grid[i][j], mi);  // 把当前值并入前缀最小值，供右下方格子使用
            }
        }
        return ans;  // 返回最大得分
    }
};