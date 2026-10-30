// 题目：3342. 到达最后一个房间的最少时间 II（Find Minimum Time to Reach Last Room II）
// 思路：与 I 同为 Dijkstra，区别是第奇数次移动耗时 2 秒、偶数次耗时 1 秒，而移动次数等于曼哈顿距离 i+j，故耗时由 (i+j)%2 决定。
// 时间复杂度：O(nm log(nm))；空间复杂度：O(nm)，用于 dist 与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minTimeToReach(vector<vector<int>>& moveTime) {  // moveTime[i][j] 是进入房间 (i,j) 的最早时刻
        int n = moveTime.size();  // 行数 n
        int m = moveTime[0].size();  // 列数 m
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));  // dist[i][j] 记录到达 (i,j) 的最早时间，初始为无穷大
        dist[0][0] = 0;  // 起点 (0,0) 在 0 时刻就已经在了
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;  // 小顶堆，按到达时间升序弹出，元素为 (时间, 行, 列)
        pq.push({0, 0, 0});  // 起点状态入堆
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向差分写法：相邻两项配对成一次 (dx, dy)

        while (1) {  // 不断取当前最早的状态（题目保证能到达终点，堆不会空）
            auto [d, i, j] = pq.top();  // 取出堆顶，即当前到达时间最小的状态
            pq.pop();  // 弹出堆顶

            if (i == n - 1 && j == m - 1) {  // 第一次弹出终点，说明已经是它最早能到达的时刻
                return d;  // 直接返回该时间即为答案
            }  // if 结束
            if (d > dist[i][j]) {  // 惰性删除：堆里残留的是该点被更新前的旧时间
                continue;  // 旧状态直接丢弃
            }  // if 结束

            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k];  // 邻居的行坐标
                int y = j + dirs[k + 1];  // 邻居的列坐标

                if (x >= 0 && x < n && y >= 0 && y < m) {  // 邻居必须落在网格内
                    int t = max(moveTime[x][y], dist[i][j]) + (i + j) % 2 + 1;  // 先等到邻居开门，再加上本步耗时：(i+j) 为偶数时 1 秒，为奇数时 2 秒
                    if (dist[x][y] > t) {  // 发现了一条更早到达邻居的路径
                        dist[x][y] = t;  // 更新邻居的最早到达时间
                        pq.push({t, x, y});  // 新状态入堆，参与后续扩展
                    }
                }  // if 结束
            }  // for 结束
        }  // while 结束
    }  // 方法结束
};  // 类定义结束
