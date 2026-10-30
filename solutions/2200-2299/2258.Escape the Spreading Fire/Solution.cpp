// 题目：2258. 逃离火灾（Escape the Spreading Fire）
// 思路：二分答案等待时间 t；check(t) 里先让火自由扩散 t 分钟，再让火与人逐分钟同步推进做 BFS，人只能走火还没烧到的空地，最终判断能否到达右下角。
// 时间复杂度：O(m * n * log(m * n))，二分 log 轮、每轮两次 BFS；空间复杂度：O(m * n)，两个布尔表和两个队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumMinutes(vector<vector<int>>& grid) {  // grid：0 空地、1 火源、2 墙；返回最多可等待的分钟数
        int m = grid.size(), n = grid[0].size();  // 网格的行数与列数
        bool vis[m][n];  // 本轮 BFS 中人是否到过某格，check 每次都要重置
        bool fire[m][n];  // 某格是否已经着火，同样在 check 开头重置
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项是 (上、右、下、左) 的行列增量
        auto spread = [&](queue<pair<int, int>>& q) {  // 让当前所有着火点向外扩散一分钟，返回新着火点的队列
            queue<pair<int, int>> nq;  // 收集这一分钟新烧起来的格子，作为下一轮的输入
            while (q.size()) {  // 逐个处理本轮已知的着火点
                auto [i, j] = q.front();  // 取出队首格子的坐标
                q.pop();  // 弹出该格子
                for (int k = 0; k < 4; ++k) {  // 检查上下左右四个相邻格
                    int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格的行列坐标
                    if (x >= 0 && x < m && y >= 0 && y < n && !fire[x][y] && grid[x][y] == 0) {  // 在界内、还没有着火、且是空地才可能被点燃
                        fire[x][y] = true;  // 标记该格已着火，防止重复入队
                        nq.emplace(x, y);  // 放进下一轮的扩散队列
                    }
                }
            }
            return nq;  // 返回这一分钟新产生的火源
        };
        auto check = [&](int t) {  // 判断「先在起点等 t 分钟再出发」能否安全逃到终点
            memset(vis, false, sizeof(vis));  // 重置人的访问标记
            memset(fire, false, sizeof(fire));  // 重置着火标记，保证多次二分调用之间互不影响
            queue<pair<int, int>> q1;  // 火 BFS 使用的队列
            for (int i = 0; i < m; ++i) {  // 逐行扫描网格
                for (int j = 0; j < n; ++j) {  // 逐列扫描网格
                    if (grid[i][j] == 1) {  // 找到初始火源
                        q1.emplace(i, j);  // 火源入队
                        fire[i][j] = true;  // 初始火源所在格立刻算作已着火
                    }
                }
            }
            for (; t && q1.size(); --t) {  // 让火先自由扩散 t 分钟（没有火可扩散时提前结束）
                q1 = spread(q1);  // 扩散一分钟并换上新产生的火源队列
            }
            if (fire[0][0]) {  // 出发点已经被火覆盖，人无法动身
                return false;  // 这个等待时间不可行
            }
            queue<pair<int, int>> q2;  // 人 BFS 使用的队列
            q2.emplace(0, 0);  // 人从左上角出发
            vis[0][0] = true;  // 标记起点已访问
            for (; q2.size(); q1 = spread(q1)) {  // 人每走一分钟，循环末尾就让火也扩散一分钟
                for (int d = q2.size(); d; --d) {  // 按层扩展：只处理当前这一分钟内可以到达的位置
                    auto [i, j] = q2.front();  // 取出队首坐标
                    q2.pop();  // 弹出队首
                    if (fire[i][j]) {  // 人到得比火晚，这一格已经被烧到
                        continue;  // 该位置作废，不能再从这里扩展
                    }
                    for (int k = 0; k < 4; ++k) {  // 尝试走向四个相邻格
                        int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格的行列坐标
                        if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && !fire[x][y] && grid[x][y] == 0) {  // 在界内、没走过、没着火且是空地才可进入
                            if (x == m - 1 && y == n - 1) {  // 正好踏进右下角终点
                                return true;  // 能逃出去，该等待时间可行
                            }
                            vis[x][y] = true;  // 标记已访问，避免重复入队
                            q2.emplace(x, y);  // 入队，下一分钟从这里继续扩展
                        }
                    }
                }
            }
            return false;  // BFS 结束仍未到终点，说明这个等待时间不可行
        };
        int l = -1, r = m * n;  // 二分区间：-1 表示不等待也走不掉，m * n 当作「无穷大」的上界
        while (l < r) {  // 二分查找可行的最大等待时间（答案是区间的右端点）
            int mid = (l + r + 1) >> 1;  // 上取整的中点，避免 l == mid 时死循环
            if (check(mid)) {  // 等待 mid 分钟可以逃生
                l = mid;  // 可行就抬高下界，答案至少是 mid
            } else {  // 等待 mid 分钟无法逃生
                r = mid - 1;  // 缩小上界
            }
        }
        return l == m * n ? 1e9 : l;  // 取到上界说明可以无限等待，按题目要求返回 1e9
    }
};