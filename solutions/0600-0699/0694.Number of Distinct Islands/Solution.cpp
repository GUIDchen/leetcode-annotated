// 题目：694. 不同岛屿的数量（Number of Distinct Islands）
// 思路：DFS 染色 + 路径签名。对每座岛按同一方向顺序遍历，进入方向 k 记 +k、离开时记 -k，这样平移后形状相同的岛会得到同一签名，用哈希集合去重后统计不同形状数。
// 时间复杂度：O(m·n)，每个格子最多访问一次；空间复杂度：O(m·n)，签名串与递归栈。
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {  // grid 为 0/1 矩阵，返回形状互不相同的岛屿数量
        unordered_set<string> paths;  // 哈希集合：存放每座岛屿的形状签名，天然去重
        string path;  // 当前岛屿的路径签名（方向序列拼成的字符串）
        int m = grid.size(), n = grid[0].size();  // m、n 分别是网格的行数与列数
        int dirs[5] = {-1, 0, 1, 0, -1};  // 4 个方向的偏移按「上、右、下、左」环形存放，末尾重复首元素便于相邻配对

        function<void(int, int, int)> dfs = [&](int i, int j, int k) {  // DFS lambda：i、j 为当前格子，k 为进入该格子的方向编号
            grid[i][j] = 0;  // 把当前格子标记为 0（已访问），避免重复统计
            path += to_string(k);  // 进入方向写入签名，记录「从哪来」
            for (int h = 1; h < 5; ++h) {  // 依次尝试上、右、下、左四个邻格（h 同时作为子方向编号）
                int x = i + dirs[h - 1], y = j + dirs[h];  // 计算邻格坐标：dirs[h-1]、dirs[h] 组成第 h-1 个方向的偏移
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y]) {  // 邻格在界内且仍是陆地才继续深搜
                    dfs(x, y, h);  // 递归访问邻格，把方向编号 h 一起传下去
                }
            }
            path += to_string(k);  // 离开时写入相反方向，保证不同形状的遍历序列不会碰撞
        };  // lambda 定义结束

        for (int i = 0; i < m; ++i) {  // 按行扫描整个网格
            for (int j = 0; j < n; ++j) {  // 按列扫描整个网格
                if (grid[i][j]) {  // 遇到未访问的陆地，说明发现一座新岛
                    dfs(i, j, 0);  // 从该格开始 DFS，方向 0 表示起点
                    paths.insert(path);  // 把整座岛的签名放入集合，形状相同会自动去重
                    path.clear();  // 清空签名缓存，准备记录下一座岛
                }
            }
        }
        return paths.size();  // 集合大小就是不同形状的岛屿数量
    }
};