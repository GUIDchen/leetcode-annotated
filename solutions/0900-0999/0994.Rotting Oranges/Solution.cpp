// 题目：994. 腐烂的橘子（Rotting Oranges）
// 思路：多源 BFS。所有腐烂橘子同时入队，每分钟向上下左右扩散一层，用 cnt 记录剩余新鲜橘子数。
// 时间复杂度：O(mn)，每个格子最多入队一次；空间复杂度：O(mn)，队列最多存放全部格子。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int orangesRotting(vector<vector<int>>& grid) {  // grid：0 空格 / 1 新鲜橘子 / 2 腐烂橘子；返回到全部腐烂所需的最少分钟数
        int m = grid.size(), n = grid[0].size();  // m、n 分别是网格的行数与列数
        queue<pair<int, int>> q;  // 多源 BFS 队列，存放所有已腐烂橘子的坐标
        int cnt = 0;  // cnt 记录当前还剩下的新鲜橘子数
        for (int i = 0; i < m; ++i) {  // 枚举每一行
            for (int j = 0; j < n; ++j) {  // 枚举每一列
                if (grid[i][j] == 1) {  // 新鲜橘子：先计数，等待被感染
                    ++cnt;  // 新鲜橘子总数加一
                } else if (grid[i][j] == 2) {  // 腐烂橘子：一开始就作为 BFS 的源点
                    q.emplace(i, j);  // 腐烂橘子坐标入队
                }  // 该格处理结束
            }  // 本行处理结束
        }  // 整个网格扫描结束
        const int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成 (dx, dy)，覆盖右下左上四个方向
        for (int ans = 1; q.size() && cnt; ++ans) {  // 按分钟分层扩散；ans 从 1 开始，因为每轮结束代表已经过去一分钟
            for (int k = q.size(); k; --k) {  // 只处理当前这一层的 q.size() 个橘子，同一层属于同一分钟
                auto [i, j] = q.front();  // 取出一个腐烂橘子坐标（结构化绑定）
                q.pop();  // 弹队
                for (int d = 0; d < 4; ++d) {  // 尝试四个方向
                    int x = i + dirs[d], y = j + dirs[d + 1];  // 计算邻居坐标
                    if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {  // 邻居在网格内且是新鲜橘子，才会被感染
                        grid[x][y] = 2;  // 标记为腐烂，避免以后重复访问
                        q.emplace(x, y);  // 新腐烂的橘子入队，下一分钟继续向外扩散
                        if (--cnt == 0) {  // 新鲜橘子已经全部感染完
                            return ans;  // 当前这一分钟结束后恰好清空，返回分钟数
                        }  // 感染分支结束
                    }  // 该邻居处理结束
                }  // 四个方向处理结束
            }  // 本层处理结束
        }  // 一分钟的扩散结束
        return cnt > 0 ? -1 : 0;  // 队列空了还有新鲜橘子说明被隔离，返回 -1；否则本来就没有新鲜橘子，返回 0
    }  // orangesRotting 函数结束
};  // 类定义结束
