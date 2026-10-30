// 3565. 顺序网格路径覆盖 / Sequential Grid Path Cover
// 核心思路：回溯搜索。从每个值为 0 或 1 的格子出发 DFS 走出一条覆盖全部 m*n 个格子的路径，用位掩码标记已访问格子，并保证经过带编号的格子时编号必须逐个递增。
// 复杂度：时间最坏 O(4^(m*n))（指数级搜索，靠剪枝收敛），空间 O(m*n)
class Solution {  // 定义解题类
    int m, n;  // 网格的行数与列数
    unsigned long long st = 0;  // 位掩码记录路径上已访问的格子
    vector<vector<int>> path;  // 记录当前路径经过的格子坐标
    int dirs[5] = {-1, 0, 1, 0, -1};  // 四个方向的增量，两两配对使用

    int f(int i, int j) {  // 把二维坐标压缩成一维编号
        return i * n + j;  // 行优先编号，用作位掩码的下标
    }  // 结束 f

    bool dfs(int i, int j, int v, vector<vector<int>>& grid) {  // 从 (i, j) 出发继续搜索，v 表示下一个应当出现的编号
        path.push_back({i, j});  // 把当前格子加入路径
        if (path.size() == static_cast<size_t>(m * n)) {  // 已经覆盖所有格子
            return true;  // 找到合法路径，直接返回成功
        }  // 结束覆盖数判断
        st |= 1ULL << f(i, j);  // 标记当前格子已访问
        if (grid[i][j] == v) {  // 当前格子带有编号
            v += 1;  // 下一个格子需要编号加一
        }  // 结束编号判断
        for (int t = 0; t < 4; ++t) {  // 枚举四个方向
            int a = dirs[t], b = dirs[t + 1];  // 取出该方向的行列增量
            int x = i + a, y = j + b;  // 计算相邻格子的坐标
            if (0 <= x && x < m && 0 <= y && y < n && (st & (1ULL << f(x, y))) == 0  // 相邻格子在界内且尚未访问
                && (grid[x][y] == 0 || grid[x][y] == v)) {  // 下一格必须为空或正好是所需编号
                if (dfs(x, y, v, grid)) {  // 递归继续搜索
                    return true;  // 子树成功则整体成功
                }  // 结束递归判断
            }  // 结束相邻格判断
        }  // 结束方向枚举
        path.pop_back();  // 回溯，撤销当前格子
        st ^= 1ULL << f(i, j);  // 清除已访问标记
        return false;  // 四个方向都走不通，返回失败
    }  // 结束 dfs

public:  // 公有接口
    vector<vector<int>> findPath(vector<vector<int>>& grid, int k) {  // 返回按编号顺序覆盖整个网格的路径
        m = grid.size();  // 记录行数
        n = grid[0].size();  // 记录列数
        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                if (grid[i][j] == 0 || grid[i][j] == 1) {  // 只能从空格或编号 1 出发
                    if (dfs(i, j, 1, grid)) {  // 从该格开始尝试搜索
                        return path;  // 成功则返回记录的路径
                    }  // 结束搜索判断
                    path.clear();  // 失败后清空路径
                    st = 0;  // 并清空访问标记
                }  // 结束起点判断
            }  // 结束列枚举
        }  // 结束行枚举
        return {};  // 找不到合法路径时返回空
    }  // 结束 findPath
};  // 结束类定义
