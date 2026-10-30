// 题目：864. 获取所有钥匙的最短路径（Shortest Path to Get All Keys）
// 思路：状态压缩 BFS。状态是 (行, 列, 已收集钥匙的二进制掩码)，锁要求掩码对应位为 1 才能通过，首次集齐全部钥匙的层数即最短步数。
// 时间复杂度：O(m·n·2^k)，k 为钥匙数量，每个状态只入队一次；空间复杂度：O(m·n·2^k)，访问标记与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const static inline vector<int> dirs = {-1, 0, 1, 0, -1};  // 四个方向的增量，相邻两项拼成一个 (dx, dy) 方向向量

    int shortestPathAllKeys(vector<string>& grid) {  // grid：迷宫地图；返回收集全部钥匙的最短步数，无法完成返回 -1
        int m = grid.size(), n = grid[0].size();  // m、n 分别为地图的行数与列数
        int k = 0;  // 钥匙总数
        int si = 0, sj = 0;  // 起点 @ 的行列坐标，先初始化为 0
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                char c = grid[i][j];  // 取出当前格子的字符
                // 累加钥匙数量（顺便统计总数 k，用于确定状态掩码上界）
                if (islower(c)) ++k;  // islower 为真说明是钥匙，统计数量
                // 起点（判断当前格子是否为 @）
                else if (c == '@')  // else if 分支：当前格子是起点 @
                    si = i, sj = j;  // 记录起点的行列坐标
            }  // 内层 for 结束
        }  // 外层 for 结束
        queue<tuple<int, int, int>> q{{{si, sj, 0}}};  // BFS 队列，元素为 (行, 列, 已收集钥匙的位掩码)
        vector<vector<vector<bool>>> vis(m, vector<vector<bool>>(n, vector<bool>(1 << k)));  // 访问标记：三维数组，第三维记录已拥有钥匙的二进制状态
        vis[si][sj][0] = true;  // 起点、未持有任何钥匙的状态标记为已访问
        int ans = 0;  // 当前 BFS 层数，即已走的步数
        while (!q.empty()) {  // 队列非空就继续扩展
            for (int t = q.size(); t; --t) {  // 一次处理完当前层的全部状态，保证层数与步数一一对应
                auto [i, j, state] = q.front();  // 取出队首状态并拆成行、列、钥匙掩码
                q.pop();  // 弹出队首
                // 找到所有钥匙，返回当前步数（位掩码全为 1 说明 k 把钥匙都已拿到）
                if (state == (1 << k) - 1) return ans;  // 集齐钥匙，当前层步数就是最短步数，立即返回
                // 往四个方向搜索（dirs 两两配对成 (dx, dy)，正好覆盖上下左右）
                for (int h = 0; h < 4; ++h) {  // 枚举 4 个方向
                    int x = i + dirs[h], y = j + dirs[h + 1];  // 由当前坐标加上方向增量，得到相邻格子的坐标
                    // 在边界范围内（只处理不越界的格子）
                    if (x >= 0 && x < m && y >= 0 && y < n) {  // 坐标越界检查
                        char c = grid[x][y];  // 取出相邻格子的字符
                        // 是墙，或者是锁，但此时没有对应的钥匙，无法通过（'#' 是墙；大写字母是锁，缺少对应钥匙时无法通过）
                        if (c == '#' || (isupper(c) && (state >> (c - 'A') & 1) == 0)) continue;  // 墙或缺钥匙的锁，跳过这个方向
                        int nxt = state;  // 下一步的钥匙状态先继承当前状态
                        // 是钥匙，更新状态（捡到钥匙就把对应位置 1）
                        if (islower(c)) nxt |= 1 << (c - 'a');  // 小写字母是钥匙，用位或把 (c - 'a') 位置 1
                        // 此状态未访问过，入队（只有 (位置, 钥匙状态) 首次出现才需要入队）
                        if (!vis[x][y][nxt]) {  // 该状态没被访问过
                            vis[x][y][nxt] = true;  // 标记为已访问，防止重复入队
                            q.push({x, y, nxt});  // 加入队列，等待下一层扩展
                        }  // if (!vis) 分支结束
                    }  // if 边界检查结束
                }  // for 方向循环结束
            }  // 当前层的 for 结束
            // 步数加一（一层扩展完毕，步数加一）
            ++ans;  // 步数加一，进入下一层
        }  // while 循环结束
        return -1;  // 队列空了仍未集齐钥匙，说明无解
    }  // shortestPathAllKeys 方法结束
};  // Solution 类定义结束