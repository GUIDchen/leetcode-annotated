// 题目：2617. 网格图中最少访问的格子数（Minimum Number of Visited Cells in a Grid）
// 思路：按行优先顺序做 BFS 式 DP，同时为每行、每列维护 (步数, 下标) 的小根堆；堆顶若已跳不到当前格子就弹出，剩下的堆顶给出到达当前格子的最小步数来源。
// 时间复杂度：O(mn log(mn))，每个格子最多入堆出堆各一次；空间复杂度：O(mn)，dist 数组与行列堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumVisitedCells(vector<vector<int>>& grid) {  // grid[i][j] 表示从该格出发向右/向下最多可走的步数；返回左上到右下的最少访问格数
        int m = grid.size(), n = grid[0].size();  // 行数 m 与列数 n
        vector<vector<int>> dist(m, vector<int>(n, -1));  // dist[i][j] 为走到该格的最少步数，-1 表示暂不可达
        using pii = pair<int, int>;  // 简写：堆中元素都是 (步数, 行或列下标)
        priority_queue<pii, vector<pii>, greater<pii>> row[m];  // 每行一个小根堆，存该行已可达格子的 (步数, 列下标)
        priority_queue<pii, vector<pii>, greater<pii>> col[n];  // 每列一个小根堆，存该列已可达格子的 (步数, 行下标)
        dist[0][0] = 1;  // 起点本身算访问 1 个格子
        for (int i = 0; i < m; ++i) {  // 行优先遍历，保证用到的来源格子都已算好
            for (int j = 0; j < n; ++j) {  // 逐列处理
                while (!row[i].empty() && grid[i][row[i].top().second] + row[i].top().second < j) {  // 堆顶格子的最远可达列已小于 j，属于过期信息
                    row[i].pop();  // 弹出过期项
                }  // 清理结束
                if (!row[i].empty() && (dist[i][j] == -1 || row[i].top().first + 1 < dist[i][j])) {  // 从本行某可达格子一步跳过来；堆顶步数最小，更优才更新
                    dist[i][j] = row[i].top().first + 1;  // 步数为来源格子步数 + 1
                }  // 行方向更新结束
                while (!col[j].empty() && grid[col[j].top().second][j] + col[j].top().second < i) {  // 列方向同理：堆顶格子的最远可达行已小于 i
                    col[j].pop();  // 弹出过期项
                }  // 清理结束
                if (!col[j].empty() && (dist[i][j] == -1 || col[j].top().first + 1 < dist[i][j])) {  // 从本列某可达格子一步跳过来，更优才更新
                    dist[i][j] = col[j].top().first + 1;  // 步数为来源格子步数 + 1
                }  // 列方向更新结束
                if (dist[i][j] != -1) {  // 该格可达，才把它的信息登记到行列堆
                    row[i].emplace(dist[i][j], j);  // 登记到所在行
                    col[j].emplace(dist[i][j], i);  // 登记到所在列
                }  // 登记结束
            }  // 本行处理结束
        }  // 全部格子处理完毕
        return dist[m - 1][n - 1];  // 终点的最少步数，不可达时即为 -1
    }  // 方法结束
};  // 题解类结束