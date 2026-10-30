// 题目：1030. 距离顺序排列矩阵单元格（Matrix Cells in Distance Order）
// 思路：从中心点做 BFS，第 k 层恰好是所有曼哈顿距离为 k 的格子，出队顺序天然满足距离升序。
// 时间复杂度：O(rows*cols)，每格只入队出队一次；空间复杂度：O(rows*cols)，队列与访问标记。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {  // 返回矩阵所有单元格按到 (rCenter, cCenter) 曼哈顿距离升序排列的结果
        queue<pair<int, int>> q;  // BFS 队列：按距离由近到远逐层扩展
        q.emplace(rCenter, cCenter);  // 把中心点作为第 0 层入队
        vector<vector<int>> ans;  // 依次存放出队顺序，即答案要求的距离升序
        bool vis[rows][cols];  // 访问标记（变长数组，行数运行时由 rows 决定）
        memset(vis, false, sizeof(vis));  // memset 按字节清零，把整张标记表置为未访问
        vis[rCenter][cCenter] = true;  // 起点立即标记，避免后面重复入队
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两两组成 (上、右、下、左) 四个偏移
        while (!q.empty()) {  // 队列非空就继续按层扩展
            for (int n = q.size(); n; --n) {  // 固定当前层长度，只处理这一层，保证同层同距离
                auto [i, j] = q.front();  // 结构化绑定：取出队首单元格的行 i 与列 j
                q.pop();  // 队首出队，表示该单元格已经被处理
                ans.push_back({i, j});  // 出队顺序就是距离升序，直接收进答案
                for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                    int x = i + dirs[k];  // 相邻格子的行坐标
                    int y = j + dirs[k + 1];  // 相邻格子的列坐标（注意 dirs[k+1] 才是列偏移）
                    if (x >= 0 && x < rows && y >= 0 && y < cols && !vis[x][y]) {  // 行列都不越界，且该格子尚未访问过
                        vis[x][y] = true;  // 先标记，防止同一格被多个邻居重复入队
                        q.emplace(x, y);  // 合法邻居入队，成为下一层
                    }  // 方向枚举结束
                }  // 当前层处理结束
            }  // 队列空，说明所有格子都已访问
        }  // 循环结束
        return ans;  // 返回按距离升序排列的全部单元格
    }  // 方法结束
};  // 类定义结束