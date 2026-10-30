// 题目：2056. 棋盘上有效移动组合的数目（Number of Valid Move Combinations On Chessboard）
// 思路：回溯枚举每个棋子的走法（原地不动，或沿某个方向走到某一格停下），用 dist 记录各棋子的逐时刻占用格，检查同一时刻同格与路径阻挡来排除冲突。
// 时间复杂度：指数级，每个棋子至多约 1 + 8 × 8 种走法；空间复杂度：O(n × 8 × 8)，每个棋子的路径占用表。
class Solution {  // 题解类
public:  // 对外接口
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {  // pieces 是棋子类型，positions 是初始坐标，返回合法移动组合数
        int n = pieces.size();  // 棋子个数
        const int m = 9;  // 棋盘坐标 1..8，用 9 作为开区间上界
        int ans = 0;  // 合法组合计数器

        vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(m, -1)));  // dist[i][x][y]：第 i 个棋子路径占用表，-1 表示该格空闲
        vector<vector<int>> end(n, vector<int>(3));  // end[i] = {最终 x, 最终 y, 停下时刻}

        const int rookDirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};  // 车的四个直线方向
        const int bishopDirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};  // 象的四个斜线方向
        const int queenDirs[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};  // 皇后的八个方向 = 车 + 象

        auto resetDist = [&](int i) {  // 清空第 i 个棋子的路径占用表
            for (int j = 0; j < m; j++) {  // 遍历棋盘行
                for (int k = 0; k < m; k++) {  // 遍历棋盘列
                    dist[i][j][k] = -1;  // 标记为“未被占用”
                }  // 列循环结束
            }  // 行循环结束
        };  // lambda 结束

        auto checkStop = [&](int i, int x, int y, int t) -> bool {  // 判断第 i 个棋子在 t 时刻停在 (x,y) 是否与更早的棋子冲突
            for (int j = 0; j < i; j++) {  // 只与下标更小的棋子比较（它们已经安排好了）
                if (dist[j][x][y] >= t) {  // 更早棋子占用该格到 t 之后，就会同时在场
                    return false;  // 撞车，该方案非法
                }  // 判断结束
            }  // 循环结束
            return true;  // 没有冲突
        };  // lambda 结束

        auto checkPass = [&](int i, int x, int y, int t) -> bool {  // 判断行进途中经过 (x,y) 的时刻 t 是否与更早棋子冲突
            for (int j = 0; j < i; j++) {  // 逐个比较更早的棋子
                if (dist[j][x][y] == t) {  // 同一时刻占用同一格，直接相撞
                    return false;  // 冲突
                }  // 判断结束
                if (end[j][0] == x && end[j][1] == y && end[j][2] <= t) {  // 更早棋子已停在该格且停下时刻不晚于 t，会挡住去路
                    return false;  // 冲突
                }  // 判断结束
            }  // 循环结束
            return true;  // 路径可行
        };  // lambda 结束

        auto isValid = [&](int x, int y) -> bool {  // 判断坐标是否在棋盘内
            return x >= 1 && x < m && y >= 1 && y < m;  // 棋盘行列都是 1..8
        };  // lambda 结束

        auto getDirs = [&](const string& piece) -> const int(*)[2] {  // 按棋子类型返回对应的方向表
            char c = piece[0];  // 取类型首字母
            if (c == 'r') {  // 车
                return rookDirs;  // 返回车的方向
            }  // 判断结束
            if (c == 'b') {  // 象
                return bishopDirs;  // 返回象的方向
            }  // 判断结束
            return queenDirs;  // 剩下的是皇后
        };  // lambda 结束

        auto dfs = [&](this auto&& dfs, int i) -> void {  // 回溯搜索：为第 i 个棋子选择一种走法
            if (i >= n) {  // 所有棋子都安排完，得到一个合法组合
                ans++;  // 计数加一
                return;  // 返回上一层
            }  // 结束

            int x = positions[i][0], y = positions[i][1];  // 第 i 个棋子的起点坐标
            resetDist(i);  // 清空它的路径记录
            dist[i][x][y] = 0;  // 起点在时刻 0 被占用
            end[i] = {x, y, 0};  // 记录“停在起点”

            if (checkStop(i, x, y, 0)) {  // 情况一：原地不动
                dfs(i + 1);  // 在不动的前提下继续安排下一个棋子
            }  // 判断结束

            const int(*dirs)[2] = getDirs(pieces[i]);  // 该棋子允许的方向表
            int dirsSize = (pieces[i][0] == 'q') ? 8 : 4;  // 皇后八向，其余四向

            for (int d = 0; d < dirsSize; d++) {  // 枚举每个方向
                resetDist(i);  // 每个方向开始前重置路径
                dist[i][x][y] = 0;  // 重新标记起点
                int nx = x + dirs[d][0], ny = y + dirs[d][1], nt = 1;  // 沿该方向的第一格坐标与时刻

                while (isValid(nx, ny) && checkPass(i, nx, ny, nt)) {  // 一格一格前进，直到出界或撞上更早的棋子
                    dist[i][nx][ny] = nt;  // 标记该格在第 nt 时刻被占用
                    end[i] = {nx, ny, nt};  // 记录新的终点
                    if (checkStop(i, nx, ny, nt)) {  // 停在这里若合法
                        dfs(i + 1);  // 就递归安排下一个棋子
                    }  // 判断结束
                    nx += dirs[d][0];  // 继续沿方向推进
                    ny += dirs[d][1];  // 列坐标同步推进
                    nt++;  // 时刻加一
                }  // 本轮推进结束
            }  // 方向枚举结束
        };  // lambda 结束

        dfs(0);  // 从第 0 个棋子开始搜索
        return ans;  // 返回组合总数
    }  // 方法结束
};  // 类定义结束
