// 题目：2711. 对角线上不同值的数量差（Difference of Number of Distinct Values on Diagonals）
// 思路：对每个格子分别向左上和右下沿对角线收集值到哈希集合，取两个集合大小之差的绝对值。
// 时间复杂度：O(m·n·(m+n))，每个格子最多扫两条对角线；空间复杂度：O(m·n + min(m,n))，结果矩阵与集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {  // grid：输入的二维矩阵
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数
        vector<vector<int>> ans(m, vector<int>(n));  // 结果矩阵，大小与 grid 相同，默认填 0
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列，处理格子 (i, j)
                int x = i, y = j;  // 用 (x, y) 作为沿对角线移动的游标
                unordered_set<int> s;  // 集合用来统计对角线上不同的值
                while (x > 0 && y > 0) {  // 往左上走，直到触碰边界
                    s.insert(grid[--x][--y]);  // 先移动再取值，收集左上对角线上的所有值
                }
                int tl = s.size();  // 左上对角线上的不同值个数
                x = i;  // 游标横坐标重置回当前格子
                y = j;  // 纵坐标同样重置
                s.clear();  // 清空集合，复用它统计右下对角线
                while (x < m - 1 && y < n - 1) {  // 往右下走，直到触碰边界
                    s.insert(grid[++x][++y]);  // 先移动再取值，收集右下对角线上的所有值
                }
                int br = s.size();  // 右下对角线上的不同值个数
                ans[i][j] = abs(tl - br);  // 题目要求：两者之差的绝对值
            }
        }
        return ans;  // 返回所有格子计算完成的结果矩阵
    }
};