// 3283. 吃掉所有兵需要的最多移动次数（Maximum Number of Moves to Kill All Pawns）
// 核心思路：先对起点和每个兵各做一次 BFS，预处理出马走到棋盘任意格的最短步数；再用状压 DP 记忆化搜索，Alice 回合取最大值、Bob 回合取最小值，枚举下一个要吃的兵。
// 复杂度：时间 O(n·m² + 2ⁿ·n²)，空间 O(2ⁿ·n)，其中 m = 50 为棋盘边长

class Solution {  // 定义题解类
public:  // 公开接口
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {  // 返回在双方都采取最优策略时 Alice 能走的最多步数
        int n = positions.size();  // 兵的数量
        const int m = 50;  // 棋盘边长固定为 50
        const int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};  // 马走日的 8 种横向偏移
        const int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};  // 马走日的 8 种纵向偏移
        int dist[n + 1][m][m];  // dist[i][x][y]：第 i 个兵（i == n 时表示起点）到格子 (x, y) 的最短马步数
        memset(dist, -1, sizeof(dist));  // 全部初始化为 -1，表示尚未访问
        for (int i = 0; i <= n; ++i) {  // 对起点和每个兵分别做一次 BFS
            int x = (i < n) ? positions[i][0] : kx;  // 第 i 个源的横坐标（i == n 时是骑士起点）
            int y = (i < n) ? positions[i][1] : ky;  // 第 i 个源的纵坐标
            queue<pair<int, int>> q;  // BFS 队列
            q.push({x, y});  // 源点入队
            dist[i][x][y] = 0;  // 源点到自身的距离为 0
            for (int step = 1; !q.empty(); ++step) {  // 按层扩展，step 记录当前层对应的步数
                for (int k = q.size(); k > 0; --k) {  // 逐层处理：本层共有 q.size() 个结点
                    auto [x1, y1] = q.front();  // 取出队首的格子
                    q.pop();  // 弹出队首
                    for (int j = 0; j < 8; ++j) {  // 枚举马的 8 种走法
                        int x2 = x1 + dx[j], y2 = y1 + dy[j];  // 走一步之后的新坐标
                        if (x2 >= 0 && x2 < m && y2 >= 0 && y2 < m && dist[i][x2][y2] == -1) {  // 新坐标仍在棋盘内，且该格尚未被访问过
                            dist[i][x2][y2] = step;  // 记录到达该格的最短马步数
                            q.push({x2, y2});  // 该格入队，等待继续向外扩展
                        }  // 结束坐标合法性判断
                    }  // 结束走法枚举
                }  // 结束本层遍历
            }  // 结束按层扩展
        }  // 结束第 i 个源的 BFS

        int f[n + 1][1 << n][2];  // f[last][state][k]：当前在 last、剩余兵集合为 state、轮到 k（1 为 Alice，0 为 Bob）时的最优结果
        memset(f, -1, sizeof(f));  // 初始化为 -1，表示该状态尚未计算
        auto dfs = [&](this auto&& dfs, int last, int state, int k) -> int {  // 记忆化搜索：last 为当前所在位置，state 为还没吃掉的兵，k 为当前行动方
            if (state == 0) {  // 兵已经全部吃完
                return 0;  // 没有剩余的移动步数可走
            }  // 结束递归边界
            if (f[last][state][k] != -1) {  // 该状态此前计算过
                return f[last][state][k];  // 直接返回缓存的结果
            }  // 结束缓存判断
            int res = (k == 1) ? 0 : INT_MAX;  // Alice 想最大化步数（初值取 0），Bob 想最小化步数（初值取无穷大）

            for (int i = 0; i < positions.size(); ++i) {  // 枚举下一个要吃掉的兵
                int x = positions[i][0], y = positions[i][1];  // 该兵的坐标
                if ((state >> i) & 1) {  // 该兵还没有被吃掉
                    int t = dfs(i, state ^ (1 << i), k ^ 1) + dist[last][x][y];  // 吃掉它：累加马步距离并交换行动方
                    if (k == 1) {  // 当前轮到 Alice
                        res = max(res, t);  // Alice 选择步数更多的方案
                    } else {  // 当前轮到 Bob
                        res = min(res, t);  // Bob 选择步数更少的方案
                    }  // 结束行动方分支
                }  // 结束该兵的判定
            }  // 结束下一个兵的枚举
            return f[last][state][k] = res;  // 记忆化并返回该状态的最优结果
        };  // lambda 定义结束
        return dfs(n, (1 << n) - 1, 1);  // 从起点（下标 n）、全部兵都还在、Alice 先手开始搜索
    }  // 方法结束
};  // 类定义结束
