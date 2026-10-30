// 题目：490. 迷宫（The Maze）
// 思路：把「球能停下的格子」作为图上的节点做 DFS；从某格沿一个方向一路滚到墙前，得到的落点才递归，vis 记录停靠过的格子，最后看终点是否被访问到。
// 时间复杂度：O(m·n)，每个格子至多入栈一次，每次扩展 4 个方向、每方向滚动 O(max(m, n))；空间复杂度：O(m·n)，vis 表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 以下成员变量在 hasPath 与 dfs 之间共享
    vector<vector<int>> maze;  // 迷宫矩阵副本：0 表示空地，1 表示墙
    vector<vector<bool>> vis;  // vis[i][j] 表示格子 (i, j) 是否作为「停靠点」被搜索过
    vector<int> d;  // 终点坐标，递归时直接取用，省去层层传参
    int m;  // 迷宫行数
    int n;  // 迷宫列数

    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {  // start：起点；destination：终点；返回球能否从起点滚到终点
        m = maze.size();  // 记录行数
        n = maze[0].size();  // 记录列数（题目保证迷宫非空）
        d = destination;  // 备份终点坐标
        vis.resize(m, vector<bool>(n, false));  // 访问表按迷宫尺寸初始化为 false
        this->maze = maze;  // 形参与成员同名，这里用 this-> 显式地把迷宫拷进成员变量
        dfs(start[0], start[1]);  // 从起点开始深搜
        return vis[d[0]][d[1]];  // 终点被访问过就说明存在可行路径
    }  // hasPath 结束

    void dfs(int i, int j) {  // 深度优先搜索：当前位置是 (i, j)
        if (vis[i][j]) return;  // 已经搜索过这个停靠点，直接返回，避免重复与死循环
        vis[i][j] = true;  // 标记本格可以停靠（即从起点可达）
        if (i == d[0] && j == d[1]) return;  // 已经到达终点，无需再向外扩展，提前剪枝
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 四个方向的行列增量：上、右、下、左
        for (int k = 0; k < 4; ++k) {  // 逐一尝试四个方向
            int x = i, y = j;  // 从当前格出发，沿这个方向一路滚动
            int a = dirs[k], b = dirs[k + 1];  // 取出当前方向的增量 a（行）、b（列）
            while (x + a >= 0 && x + a < m && y + b >= 0 && y + b < n && maze[x + a][y + b] == 0) {  // 只要下一格仍在界内且不是墙，球就会继续滚（遇到墙或边界才停）
                x += a;  // 行坐标滚进一格
                y += b;  // 列坐标滚进一格
            }  // 这个方向的滚动结束，停在了障碍前
            dfs(x, y);  // 从新的停靠点继续深搜（若原地没动，会因 vis 已标记而立即返回）
        }  // 四个方向尝试完毕
    }  // dfs 结束
};  // 类定义结束