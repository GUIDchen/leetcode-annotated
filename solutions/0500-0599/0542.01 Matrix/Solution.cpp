// 题目：542. 01 矩阵（01 Matrix）
// 思路：多源 BFS。先把所有 0 当作源点入队，再逐层向外扩展，每个 1 第一次被访问时的层数就是它到最近 0 的距离。
// 时间复杂度：O(m*n)，每个格子最多入队一次；空间复杂度：O(m*n)，答案矩阵与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {  // mat 是只含 0/1 的矩阵，返回每个位置到最近 0 的曼哈顿距离
        int m = mat.size(), n = mat[0].size();  // m、n 分别是矩阵的行数与列数
        vector<vector<int>> ans(m, vector<int>(n, -1));  // 答案矩阵，先全部填 -1 表示「尚未计算距离」，同时兼作访问标记
        queue<pair<int, int>> q;  // BFS 队列，存放待向外扩展的坐标
        for (int i = 0; i < m; ++i) {  // 第一遍扫描：把所有 0 作为多源 BFS 的起点
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                if (mat[i][j] == 0) {  // 遇到值为 0 的格子
                    ans[i][j] = 0;  // 0 到自己的距离就是 0
                    q.emplace(i, j);  // 把它入队，作为距离扩展的源点
                }
            }
        }
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 四个方向的偏移量：上下左右，(dirs[i], dirs[i+1]) 成对取值
        while (!q.empty()) {  // 队列非空说明还有可向外扩展的格子
            auto p = q.front();  // 取出队首坐标（本层已确定距离的格子）
            q.pop();  // 弹出队首，避免重复处理
            for (int i = 0; i < 4; ++i) {  // 依次尝试四个相邻方向
                int x = p.first + dirs[i];  // 相邻格子的行下标
                int y = p.second + dirs[i + 1];  // 相邻格子的列下标（与 dirs[i] 组成一组方向偏移）
                if (x >= 0 && x < m && y >= 0 && y < n && ans[x][y] == -1) {  // 位置合法且该格子还没被赋值，说明这是它第一次被最短路访问到
                    ans[x][y] = ans[p.first][p.second] + 1;  // 距离等于当前格子距离加 1，BFS 保证这是最近 0 的距离
                    q.emplace(x, y);  // 新格子入队，继续向外扩展
                }
            }
        }
        return ans;  // 返回填好的距离矩阵
    }
};