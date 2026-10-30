// 4003. 交替方向的最小路径代价 III / Minimum Cost Path with Alternating Directions III（困难）
// 核心思路：把「下一步行动编号的奇偶性要求」作为第二维状态（1 表示下一步是奇数编号、只能右/下，0 表示偶数编号、只能左/上），在 (行, 列, 状态) 上跑 Dijkstra；进入格子付 (i+1)*(j+1)，违反奇偶规则移动或原地等待再付 penalty[i][j]，每一步之后状态翻转。
// 复杂度：时间 O(m n log(m n))，空间 O(m n)。
class Solution {  // 题解类
public:  // 公有接口
    long long minCost(int m, int n, vector<vector<int>>& penalty) {  // 返回从 (0, 0) 走到 (m-1, n-1) 的最小总代价
        vector<vector<array<long long, 2>>> dist(  // dist[i][j][k]：到达 (i, j) 且下一步奇偶性要求为 k 时的最小代价
            m, vector<array<long long, 2>>(n, {LLONG_MAX, LLONG_MAX}));  // 初始化全部为无穷大，第二维大小为 2（两种奇偶性要求）
        dist[0][0][1] = 1;  // 起点入口代价 (0+1)*(0+1) = 1，且行动编号从 1 开始（奇数，对应状态 1）

        priority_queue<  // 小根堆：按代价从小到大出堆
            array<long long, 4>,  // 堆元素：{代价, 行, 列, 状态}
            vector<array<long long, 4>>,  // 底层容器
            greater<>>  // 比较器，使代价最小者优先
            pq;  // 优先队列对象
        pq.push({1, 0, 0, 1});  // 起点状态入堆

        int dirs[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};  // 四个方向：上、右、左、下（下标奇偶区分竖向与横向）

        while (!pq.empty()) {  // Dijkstra 主循环
            auto [d, i, j, k] = pq.top();  // 取出当前代价最小的状态
            pq.pop();  // 出堆

            if (i == m - 1 && j == n - 1) {  // 第一次弹出终点时即为最小代价
                return d;  // 直接返回最小总代价
            }  // if 结束
            if (d > dist[i][j][k]) {  // 该状态已被更优的路径更新过，是过期状态
                continue;  // 跳过，避免重复扩展
            }  // if 结束

            int p = penalty[i][j];  // 当前格子原地等待的惩罚代价

            long long nd = d + p;  // 原地等待一步：支付 penalty，行动编号加一
            if (nd < dist[i][j][k ^ 1]) {  // 等待后奇偶性要求翻转，看能否松弛
                dist[i][j][k ^ 1] = nd;  // 更新更优代价
                pq.push({nd, i, j, k ^ 1});  // 新状态入堆
            }  // if 结束

            for (int idx = 0; idx < 4; idx++) {  // 枚举四个相邻方向
                int x = i + dirs[idx][0];  // 目标行
                int y = j + dirs[idx][1];  // 目标列
                if (0 <= x && x < m && 0 <= y && y < n) {  // 目标格必须在网格内
                    nd = d + 1LL * (x + 1) * (y + 1) + (((idx & 1) ^ k) ? p : 0);  // 进入目标格的入口代价；本步方向违反奇偶规则时再加 penalty
                    if (nd < dist[x][y][k ^ 1]) {  // 新状态可被松弛
                        dist[x][y][k ^ 1] = nd;  // 更新更优代价
                        pq.push({nd, (long long) x, (long long) y, (long long) (k ^ 1)});  // 新状态入堆
                    }  // if 结束
                }  // if 结束
            }  // for 结束
        }  // while 结束

        return -1;  // 环里等待总可以走完，这里只是兜底
    }  // 方法结束
};  // 类定义结束