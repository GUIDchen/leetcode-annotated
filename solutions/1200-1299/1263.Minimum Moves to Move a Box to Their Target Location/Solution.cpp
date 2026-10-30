// 题目：1263. 推箱子（Minimum Moves to Move a Box to Their Target Location）
// 思路：把状态定义为（人的位置，箱子的位置）；人空走边权为 0、推箱子边权为 1，用双端队列做 0-1 BFS，首次取出目标状态时的距离即最少推动次数。
// 时间复杂度：O((mn)²)，共 mn×mn 个状态、每个状态 4 次转移；空间复杂度：O((mn)²)，vis 二维标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minPushBox(vector<vector<char>>& grid) {  // grid 是字符网格：'S' 人、'B' 箱子、'T' 目标、'#' 障碍、'.' 空地
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        int si, sj, bi, bj;  // 先声明人与箱子的坐标，下面扫网格时填入
        for (int i = 0; i < m; ++i) {  // 逐行扫描网格
            for (int j = 0; j < n; ++j) {  // 逐列扫描网格
                if (grid[i][j] == 'S') {  // 找到人的起点
                    si = i, sj = j;  // 记下人的初始位置
                } else if (grid[i][j] == 'B') {  // 否则判断是否是箱子的起点
                    bi = i, bj = j;  // 记下箱子的初始位置
                }  // 结束起点判断
            }  // 结束列扫描
        }  // 结束行扫描
        auto f = [&](int i, int j) {  // 坐标压缩函数：把 (i, j) 映射成唯一的一维编号
            return i * n + j;  // 行优先编号：i * n + j
        };  // 结束 lambda
        auto check = [&](int i, int j) {  // 合法性判断：坐标不越界且该格不是墙
            return i >= 0 && i < m && j >= 0 && j < n && grid[i][j] != '#';  // 同时检查四个边界与障碍物
        };  // 结束 lambda
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四个方向的增量交错排列：dirs[k] 是行增量、dirs[k+1] 是列增量，首尾都是 -1 便于成对取用
        deque<tuple<int, int, int>> q;  // 双端队列，0-1 BFS 中代价 0 进队首、代价 1 进队尾，保证队首始终是当前距离最小的状态
        q.emplace_back(f(si, sj), f(bi, bj), 0);  // 初始状态：人在 si,sj、箱子在 bi,bj，已推 0 次
        bool vis[m * n][m * n];  // vis[人的编号][箱子的编号] 标记该二元状态是否已入队
        memset(vis, false, sizeof(vis));  // 全部置为未访问
        vis[f(si, sj)][f(bi, bj)] = true;  // 标记初始状态已访问，避免重复入队
        while (!q.empty()) {  // 队列非空就一直搜索
            auto [s, b, d] = q.front();  // 结构化绑定取出：s 人编号、b 箱子编号、d 当前已用推动次数
            q.pop_front();  // 该状态已出队，从队首移除
            si = s / n, sj = s % n;  // 把人的编号还原成行、列坐标
            bi = b / n, bj = b % n;  // 把箱子的编号还原成行、列坐标
            if (grid[bi][bj] == 'T') {  // 箱子已经停在目标格
                return d;  // 0-1 BFS 保证首次取出的目标状态距离最小，直接返回 d
            }  // 结束目标判断
            for (int k = 0; k < 4; ++k) {  // 枚举人尝试移动的四个方向
                int sx = si + dirs[k], sy = sj + dirs[k + 1];  // 人朝该方向走一步后的坐标
                if (!check(sx, sy)) {  // 越界或撞墙则这个人无法移动，本方向放弃
                    continue;  // 跳过本次枚举
                }  // 结束合法性判断
                if (sx == bi && sy == bj) {  // 人要走的格子正是箱子所在，说明这一步是在推箱子
                    int bx = bi + dirs[k], by = bj + dirs[k + 1];  // 箱子被推到人前方的下一格
                    if (!check(bx, by) || vis[f(sx, sy)][f(bx, by)]) {  // 箱子被推的位置不合法，或该二元状态已经访问过
                        continue;  // 跳过本次枚举
                    }  // 结束推箱子合法性判断
                    vis[f(sx, sy)][f(bx, by)] = true;  // 标记新状态：人站到箱子原位、箱子前进一格
                    q.emplace_back(f(sx, sy), f(bx, by), d + 1);  // 推动一次代价为 1，因此放到队尾
                } else if (!vis[f(sx, sy)][f(bi, bj)]) {  // 否则箱子不动，只是人空走一步；状态未访问才继续处理
                    vis[f(sx, sy)][f(bi, bj)] = true;  // 标记该状态已访问
                    q.emplace_front(f(sx, sy), f(bi, bj), d);  // 空走代价为 0，放到队首，使队列按推动次数非递减
                }  // 结束推 / 走的两种分支
            }  // 结束四方向枚举
        }  // 结束 while 循环
        return -1;  // 队列空仍未碰到目标：箱子无法被推到 T，返回 -1
    }  // 结束 minPushBox
};  // 结束题解类