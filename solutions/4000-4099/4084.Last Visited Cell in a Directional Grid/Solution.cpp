// 题目：4084. 有向网格中的最后访问单元格（Last Visited Cell in a Directional Grid）
// 核心思路：从 (0,0) 出发，按当前格子的箭头（L/R/U/D）不断移动，并用 vis 记录走过的格子；一旦下一步越界或踩到已访问过的格子就停下，返回停下前所在的那一格坐标。
// 复杂度：时间 O(m*n)，每个格子最多访问一次；空间 O(m*n)，用于访问标记。
class Solution {  // LeetCode 约定的题解类
public:  // 公开接口
    vector<int> lastVisitedCell(vector<vector<char>>& grid) {  // grid：由 'L','R','U','D' 组成的有向网格；返回最后停留的单元格 [行, 列]
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        int r = 0, c = 0;  // 当前位置的行列下标，从左上角 (0, 0) 出发
        vector<vector<bool>> vis(m, vector<bool>(n));  // vis 标记某个格子是否已经访问过，默认全为 false
        while (true) {  // 一直沿箭头移动，直到无法再走为止
            vector<int> cur = {r, c};  // 先记下进入此格时的坐标，作为可能的最终答案
            vis[r][c] = true;  // 把当前格子标记为已访问
            switch (grid[r][c]) {  // 根据当前格子的箭头字符分派下一步移动
            case 'L': c--; break;  // 'L'：列号减一，向左一格
            case 'R': c++; break;  // 'R'：列号加一，向右一格
            case 'U': r--; break;  // 'U'：行号减一，向上一格
            case 'D': r++; break;  // 'D'：行号加一，向下一格
            }  // 方向分派结束
            if (r >= 0 && r < m && c >= 0 && c < n && !vis[r][c]) {  // 下一步仍在网格内且未被访问过，说明可以继续走
                continue;  // 更新后的坐标合法，进入下一轮移动
            }  // 可继续判断结束
            return cur;  // 越界或重复访问，返回当前停留的格子坐标
        }  // while 循环结束（正常不会走到这里）
    }  // lastVisitedCell 结束
};  // Solution 类结束