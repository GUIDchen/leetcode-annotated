// 题目：807. 保持城市天际线（Max Increase to Keep City Skyline）
// 思路：先求每行、每列的最大值作为两个方向的天际线，每个格子能增加到的上限就是两者较小值，累加差值就是答案。
// 时间复杂度：O(mn)；空间复杂度：O(m + n)，只存行、列最大值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {  // grid：建筑高度矩阵；返回所有建筑可以增加的总高度
        int m = grid.size();  // 行数
        int n = grid[0].size();  // 列数
        vector<int> rowMax(m);  // 每行最大值，即从左右方向看的天际线
        vector<int> colMax(n);  // 每列最大值，即从前后方向看的天际线
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                rowMax[i] = max(rowMax[i], grid[i][j]);  // 更新该行的天际线
                colMax[j] = max(colMax[j], grid[i][j]);  // 更新该列的天际线
            }  // 内层循环结束
        }  // 外层循环结束
        int ans = 0;  // 累加可以增加的总高度
        for (int i = 0; i < m; ++i) {  // 再次遍历每个格子
            for (int j = 0; j < n; ++j) {  // 逐个计算该格子的可增高量
                ans += min(rowMax[i], colMax[j]) - grid[i][j];  // 上限是两个天际线的较小值，减去原高度就是增量
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回总增量
    }  // 方法结束
};  // 类定义结束