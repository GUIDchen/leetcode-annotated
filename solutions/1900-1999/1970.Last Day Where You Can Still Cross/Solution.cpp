// 题目：1970. 你能穿过矩阵的最后一天（Last Day Where You Can Still Cross）
// 思路：能通过的天数具有单调性（第 k 天能过则更早的日子一定能过），于是对天数二分；判定时把前 k 天被淹的格子当作障碍，用多源 BFS 从第 0 行所有陆地出发，看能否到达第 row-1 行。
// 时间复杂度：O(row * col * log(row * col))，二分 log 次、每次 BFS 扫一遍网格；空间复杂度：O(row * col)，网格与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {  // row/col：网格行数与列数；cells[i] 是第 i+1 天被水淹没的格子
        int l = 1, r = cells.size();  // 二分区间：天数从第 1 天到第 cells.size() 天
        int g[row][col];  // 网格状态数组：1 表示水或已访问，0 表示可走的陆地
        int dirs[5] = {0, 1, 0, -1, 0};  // 四个方向的紧凑写法：(dirs[i], dirs[i+1]) 即第 i 个方向的偏移
        auto check = [&](int k) -> bool {  // 判定第 k 天是否还能从最上行走通到最下行
            memset(g, 0, sizeof(g));  // 每次判定前把网格清零
            for (int i = 0; i < k; ++i) {  // 把前 k 天被淹的格子都标记成水
                g[cells[i][0] - 1][cells[i][1] - 1] = 1;  // 输入坐标是 1-based，减 1 换成 0-based
            }
            queue<pair<int, int>> q;  // BFS 队列，存放待扩展的格子坐标
            for (int j = 0; j < col; ++j) {  // 最上行的每个陆地格子都是起点（多源 BFS）
                if (g[0][j] == 0) {  // 当前格子还是陆地
                    q.emplace(0, j);  // 作为起点入队
                    g[0][j] = 1;  // 入队即标记为已访问，避免重复入队
                }
            }
            while (!q.empty()) {  // 队列非空就继续向外扩展
                auto [x, y] = q.front();  // 取出队首坐标（结构化绑定）
                q.pop();  // 弹出队首元素
                if (x == row - 1) {  // 已经到达最后一行，说明可以穿过
                    return true;  // 提前返回成功
                }
                for (int i = 0; i < 4; ++i) {  // 枚举上、右、下、左四个方向
                    int nx = x + dirs[i];  // 相邻格的行号
                    int ny = y + dirs[i + 1];  // 相邻格的列号
                    if (nx >= 0 && nx < row && ny >= 0 && ny < col && g[nx][ny] == 0) {  // 坐标合法且该格是未访问的陆地
                        q.emplace(nx, ny);  // 入队等待继续扩展
                        g[nx][ny] = 1;  // 入队时立刻标记，防止同一格被多次入队
                    }
                }
            }
            return false;  // BFS 结束仍未到最下行，说明第 k 天走不通
        };
        while (l < r) {  // 二分查找最后一个「能通过」的天数
            int mid = (l + r + 1) >> 1;  // 中点向上取整，避免只剩两个元素时死循环
            if (check(mid)) {  // 第 mid 天能通过
                l = mid;  // 答案至少是 mid，收缩左边界
            } else {  // 第 mid 天过不去
                r = mid - 1;  // 答案一定小于 mid
            }
        }
        return l;  // 循环结束时 l == r，即最后能穿过的天数
    }
};
