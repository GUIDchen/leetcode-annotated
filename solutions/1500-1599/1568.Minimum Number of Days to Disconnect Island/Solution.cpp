// 题目：1568. 使陆地分离的最少天数（Minimum Number of Days to Disconnect Island）
// 思路：答案只可能是 0/1/2；先数连通块，已不是一块就返回 0，再尝试删掉每个陆地格子看能否分离，能则返回 1，否则返回 2。
// 时间复杂度：O(m^2 * n^2)，每个格子都做一次 O(mn) 的连通块统计；空间复杂度：O(mn)，递归栈与访问标记。
class Solution {  // LeetCode 约定的题解类
public:  // 成员对外可见
    const vector<int> dirs = {-1, 0, 1, 0, -1};  // 四方向偏移，相邻两项组合成一个 (dx, dy)
    int m, n;  // 网格的行数 m 与列数 n，供各个成员函数共享

    int minDays(vector<vector<int>>& grid) {  // grid：0/1 网格，1 表示陆地
        m = grid.size(), n = grid[0].size();  // 记录网格尺寸
        if (count(grid) != 1) {  // 本来就不是完整的一块（0 块或已分离）
            return 0;  // 无需任何操作
        }
        for (int i = 0; i < m; ++i) {  // 枚举每一行
            for (int j = 0; j < n; ++j) {  // 枚举每一列
                if (grid[i][j] == 1) {  // 只尝试把陆地格子变成水
                    grid[i][j] = 0;  // 试删这个格子
                    if (count(grid) != 1) {  // 删除后连通块数量不再是 1
                        return 1;  // 只需一天
                    }
                    grid[i][j] = 1;  // 恢复现场，继续尝试下一个格子
                }
            }
        }
        return 2;  // 任何一块陆地都能靠删掉至多两个格子分离，所以最多需要两天
    }

    int count(vector<vector<int>>& grid) {  // 统计网格中陆地连通块的个数
        int cnt = 0;  // 连通块计数
        for (int i = 0; i < m; ++i) {  // 遍历所有行
            for (int j = 0; j < n; ++j) {  // 遍历所有列
                if (grid[i][j] == 1) {  // 发现尚未访问的陆地
                    dfs(i, j, grid);  // 洪水填充整块陆地
                    ++cnt;  // 连通块数量加一
                }
            }
        }
        for (int i = 0; i < m; ++i) {  // 还原：把访问标记改回陆地
            for (int j = 0; j < n; ++j) {  // 遍历所有列
                if (grid[i][j] == 2) {  // 2 是本次搜索留下的访问标记
                    grid[i][j] = 1;  // 恢复成陆地 1
                }
            }
        }
        return cnt;  // 返回连通块个数
    }

    void dfs(int i, int j, vector<vector<int>>& grid) {  // 从 (i, j) 出发标记整块陆地
        grid[i][j] = 2;  // 标记为已访问，避免重复搜索
        for (int k = 0; k < 4; ++k) {  // 枚举四个方向
            int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居的坐标
            if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {  // 邻居在界内且是未访问的陆地
                dfs(x, y, grid);  // 继续递归填充
            }
        }
    }
};