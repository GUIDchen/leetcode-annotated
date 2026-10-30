// 题目：2577. 在网格图中访问一个格子的最少时间（Minimum Time to Visit a Cell In a Grid）
// 思路：把「最早到达时刻」当作最短路距离，用小根堆做 Dijkstra；若邻居还没开放，就在相邻格之间来回抖动，凑到不早于开放时间且奇偶相同的最早时刻。
// 时间复杂度：O(mn log(mn))，每个格子最多入堆常数次；空间复杂度：O(mn)，dist 数组与堆都要存 O(mn) 个状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTime(vector<vector<int>>& grid) {  // grid[x][y] 是格子 (x,y) 的开放时间，返回从左上角到右下角的最早时刻
        if (grid[0][1] > 1 && grid[1][0] > 1) {  // 起点右边和下边都要等到时刻 1 之后才开放，第 0 秒一步都走不了，必然无解
            return -1;  // 无法出发，直接返回 -1
        }
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数
        int dist[m][n];  // dist[x][y] 记录到达 (x,y) 的最早时刻；这里用边长可变的数组，大小正好贴合网格
        memset(dist, 0x3f, sizeof dist);  // 用 0x3f 按字节填充，相当于把每个格子的最早到达时刻初始化为一个足够大的数
        dist[0][0] = 0;  // 起点在第 0 秒就已到达，不需要等待
        using tii = tuple<int, int, int>;  // 给堆元素起别名：三元组 (当前时刻, 行, 列)
        priority_queue<tii, vector<tii>, greater<tii>> pq;  // 小根堆：每次都先取出时刻最小的状态，这正是 Dijkstra 需要的顺序
        pq.emplace(0, 0, 0);  // 把起点状态压入堆，作为扩展的起点
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四个方向用「上、右、下、左」的相邻偏移量表示，第 k 个方向对应 (dirs[k], dirs[k+1])
        while (1) {  // 只要堆里还有状态就继续扩展；答案命中终点后会提前 return
            auto [t, i, j] = pq.top();  // 取出当前时刻最小的状态，t 为最早到达时刻，i、j 为坐标
            pq.pop();  // 该状态已取出，立即出堆，避免重复处理
            if (i == m - 1 && j == n - 1) {  // 走到了终点，因为是小根堆，此刻的 t 就是最小时间
                return t;  // 返回最早到达终点的时刻
            }
            for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 算出邻居坐标 (x, y)
                if (x >= 0 && x < m && y >= 0 && y < n) {  // 邻居必须落在网格内部，越界就跳过
                    int nt = t + 1;  // 相邻格子之间走一步只花 1 秒，先假设立刻走过去
                    if (nt < grid[x][y]) {  // 目标格子这时还没开放，必须等待
                        nt = grid[x][y] + (grid[x][y] - nt) % 2;  // 只能靠来回抖动耗掉偶数秒，所以用 (开放时间 - 到达时间) % 2 补齐奇偶差，得到不早于开放时间的最早时刻
                    }
                    if (nt < dist[x][y]) {  // 松弛：只有更早到达 (x,y) 时才值得更新
                        dist[x][y] = nt;  // 更新 (x,y) 的最早到达时刻
                        pq.emplace(nt, x, y);  // 把新状态压入堆，等待后续扩展
                    }
                }
            }
        }
    }
};  // 类定义结束