// 题目：54. 螺旋矩阵（Spiral Matrix）
// 思路：模拟。用方向数组表示右、下、左、上四个方向，每走一步就检查下一步是否越界或已访问，是就顺时针转向。
// 时间复杂度：O(m*n)，每个格子恰好访问一次；空间复杂度：O(m*n)，额外的访问标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> spiralOrder(vector<vector<int>>& matrix) {  // matrix 为 m 行 n 列的矩阵，按螺旋顺序返回其中的元素
        int m = matrix.size(), n = matrix[0].size();  // m 是行数，n 是列数
        int dirs[5] = {0, 1, 0, -1, 0};  // 方向数组：右、下、左、上；第 k 个方向的行增量为 dirs[k]，列增量为 dirs[k+1]
        int i = 0, j = 0, k = 0;  // 当前位置 (i, j) 与当前方向下标 k，从 (0,0) 向右开始
        vector<int> ans;  // 按螺旋顺序收集结果
        bool vis[m][n];  // 访问标记，避免重复走进已经取过的格子
        memset(vis, false, sizeof(vis));  // 把整张标记表清成 false
        for (int h = m * n; h; --h) {  // 一共需要取 m*n 个格子，每轮取一个
            ans.push_back(matrix[i][j]);  // 记录当前格子的值
            vis[i][j] = true;  // 标记当前格子已访问
            int x = i + dirs[k], y = j + dirs[k + 1];  // 试探沿当前方向走一步会到达的位置 (x, y)
            if (x < 0 || x >= m || y < 0 || y >= n || vis[x][y]) {  // 越界或已经访问过，说明必须在这里转弯
                k = (k + 1) % 4;  // 顺时针切到下一个方向（右→下→左→上循环）
            }  // 按（可能刚更新过的）方向移动行坐标
            i += dirs[k];  // 按同方向移动列坐标
            j += dirs[k + 1];  // for 结束
        }  // 返回螺旋顺序的结果
        return ans;  // spiralOrder 结束
    }  // 类定义结束
};