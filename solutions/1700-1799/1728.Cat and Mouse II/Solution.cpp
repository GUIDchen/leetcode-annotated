// 题目：1728. 猫和老鼠 II（Cat and Mouse II）
// 思路：把 (老鼠位置, 猫位置, 轮到谁走) 当作状态，从已知终局出发反向 BFS 推胜负；用出度计数处理「所有后继都对当前方不利则当前方必败」。
// 时间复杂度：O(V^2 * E)，V 为可走格子数、E 为每格可跳达的格子数；空间复杂度：O(V^2)，需要保存每个状态的结论与出度。
class Solution {  // LeetCode 约定的题解类
private:  // 以下为内部辅助函数，只服务于 canMouseWin
    const int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向增量表：相邻两项组成 (dx, dy)

    int calc(vector<vector<int>>& gMouse, vector<vector<int>>& gCat, int mouseStart, int catStart, int hole) {  // 反向 BFS 求起点结论：1 老鼠胜、2 猫胜
        int n = gMouse.size();  // 编号空间大小（按 m*n 计算，未按可走格压缩）
        vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2)));  // degree[m][c][t]：该状态还有多少个后继结论未知，t 为轮次
        vector<vector<vector<int>>> ans(n, vector<vector<int>>(n, vector<int>(2)));  // ans[m][c][t]：该状态的结论，0 未知、1 老鼠胜、2 猫胜
        queue<tuple<int, int, int>> q;  // BFS 队列，元素是 (老鼠, 猫, 轮到谁走)

        // 第一段：把每个状态的出度填好
        for (int i = 0; i < n; i++) {  // 枚举老鼠所在位置
            for (int j = 0; j < n; j++) {  // 枚举猫所在位置
                degree[i][j][0] = gMouse[i].size();  // 轮到老鼠时，出度就是老鼠在该格的可走步数
                degree[i][j][1] = gCat[j].size();  // 轮到猫时，出度由猫在该格的可走步数决定
            }  // 猫位置枚举结束
        }  // 出度初始化完成

        // 第二段：把所有已知终局压入队列
        for (int i = 0; i < n; i++) {  // 用同一个 i 同时枚举两个棋子的位置
            ans[hole][i][1] = 1;  // 轮到猫走而老鼠已在食物格：老鼠胜
            ans[i][hole][0] = 2;  // 轮到老鼠走而猫已在食物格：猫先吃到食物，猫胜
            ans[i][i][1] = 2;  // 同一格且轮到猫：猫当场抓住老鼠，猫胜
            ans[i][i][0] = 2;  // 同一格且轮到老鼠：老鼠已被抓，猫胜
            q.push(make_tuple(hole, i, 1));  // 把上面四个终局状态依次入队
            q.push(make_tuple(i, hole, 0));  // 老鼠已在食物格，轮到猫走
            q.push(make_tuple(i, i, 0));  // 两只都在同一格，轮到老鼠走
            q.push(make_tuple(i, i, 1));  // 两只都在同一格，轮到猫走
        }  // 终局状态入队完毕

        // 第三段：反向 BFS，把结论沿着前驱状态传播出去
        while (!q.empty()) {  // 队列非空就继续扩展
            auto state = q.front();  // 取出队头状态
            q.pop();  // 弹出队头
            int m = get<0>(state), c = get<1>(state), t = get<2>(state);  // 拆出老鼠位置 m、猫位置 c、轮次 t
            int result = ans[m][c][t];  // 这个已知结论将传递给它的所有前驱
            for (auto& prevState : getPrevStates(gMouse, gCat, state, ans)) {  // 枚举一步就能走到 state 的所有前驱状态
                int pm = get<0>(prevState), pc = get<1>(prevState), pt = get<2>(prevState);  // 拆出前驱的老鼠、猫、轮次
                if (pt == result - 1) {  // 前驱轮次与结论相反：前驱方一步就能走到对自己有利的状态
                    ans[pm][pc][pt] = result;  // 前驱立刻得到同一结论
                    q.push(prevState);  // 前驱结论确定，入队继续传播
                } else {  // 前驱与结论同轮次：前驱方走到的是对自己不利的状态
                    degree[pm][pc][pt]--;  // 该前驱的可用后继少一个
                    if (degree[pm][pc][pt] == 0) {  // 所有后继都对前驱方不利
                        ans[pm][pc][pt] = result;  // 前驱方必败，继承同一结论
                        q.push(prevState);  // 前驱结论确定，入队继续传播
                    }  // 出度判断结束
                }  // 胜负判断结束
            }  // 前驱枚举结束
        }  // 队列清空，所有可达状态的结论都已推出

        return ans[mouseStart][catStart][0];  // 返回题意起点（轮到老鼠走）的结论
    }  // calc 结束

    vector<tuple<int, int, int>> getPrevStates(vector<vector<int>>& gMouse, vector<vector<int>>& gCat, tuple<int, int, int>& state, vector<vector<vector<int>>>& ans) {  // 求一步能到达 state 的所有前驱状态
        int m = get<0>(state), c = get<1>(state), t = get<2>(state);  // 拆出当前状态的老鼠、猫、轮次
        int pt = t ^ 1;  // 前驱轮次必然与当前相反：0 和 1 用异或互换
        vector<tuple<int, int, int>> pre;  // 收集前驱状态
        if (pt == 1) {  // 前驱轮到猫走，只有猫的位置可能变化
            for (int pc : gCat[c]) {  // 枚举猫从当前位置一步能到达的格子
                if (ans[m][pc][1] == 0) {  // 只保留结论还没确定的前驱，避免重复入队
                    pre.push_back(make_tuple(m, pc, pt));  // 记录这个前驱
                }  // 过滤结束
            }  // 猫的走法枚举结束
        } else {  // 前驱轮到老鼠走，只有老鼠的位置可能变化
            for (int pm : gMouse[m]) {  // 枚举老鼠从当前位置一步能到达的格子
                if (ans[pm][c][0] == 0) {  // 同样只保留结论未知的前驱
                    pre.push_back(make_tuple(pm, c, 0));  // 第三项固定为 0，表示轮到老鼠走
                }  // 过滤结束
            }  // 老鼠的走法枚举结束
        }  // 分支结束
        return pre;  // 返回前驱列表
    }  // getPrevStates 结束

public:  // 题解方法对外可见
    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {  // grid 是棋盘，catJump/mouseJump 是两者各自的最大跳跃距离
        int m = grid.size();  // 棋盘行数
        int n = grid[0].length();  // 棋盘列数
        int catStart = 0, mouseStart = 0, food = 0;  // 猫、老鼠、食物三者的位置编号
        vector<vector<int>> gMouse(m * n);  // 每个格子按老鼠规则一步能到达的格子列表
        vector<vector<int>> gCat(m * n);  // 每个格子按猫规则一步能到达的格子列表

        // 第一步：把棋盘按行优先编号，同时建出两个棋子各自的可达图
        for (int i = 0; i < m; i++) {  // 枚举行
            for (int j = 0; j < n; j++) {  // 枚举列
                char c = grid[i][j];  // 当前格子的字符
                if (c == '#') {  // 障碍格不建立任何边
                    continue;  // 直接跳过这个格子
                }  // 障碍判断结束
                int v = i * n + j;  // 二维坐标压成一维编号
                if (c == 'C') {  // 当前格是猫的起点
                    catStart = v;  // 保存猫的起点编号
                } else if (c == 'M') {  // 当前格是老鼠的起点
                    mouseStart = v;  // 保存老鼠的起点编号
                } else if (c == 'F') {  // 当前格是食物
                    food = v;  // 保存食物的编号
                }  // 起点识别结束

                for (int d = 0; d < 4; ++d) {  // 枚举四个方向
                    for (int k = 0; k <= mouseJump; k++) {  // 老鼠沿该方向最多跳 mouseJump 步，k = 0 表示原地
                        int x = i + k * dirs[d];  // 目标行
                        int y = j + k * dirs[d + 1];  // 目标列
                        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '#') {  // 越界或撞墙
                            break;  // 再往前必然也不可达，直接结束这个方向
                        }  // 合法性判断结束
                        gMouse[v].push_back(x * n + y);  // 记录老鼠从 v 可一步到达该格
                    }  // 老鼠的跳跃枚举结束
                    for (int k = 0; k <= catJump; k++) {  // 猫沿同一方向最多跳 catJump 步
                        int x = i + k * dirs[d];  // 目标行
                        int y = j + k * dirs[d + 1];  // 目标列
                        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '#') {  // 越界或撞墙
                            break;  // 同方向后续格子都不可达，跳出
                        }  // 合法性判断结束
                        gCat[v].push_back(x * n + y);  // 记录猫从 v 可一步到达该格
                    }  // 猫的跳跃枚举结束
                }  // 方向枚举结束
            }  // 列枚举结束
        }  // 棋盘扫描结束

        // 第二步：在状态图上反向 BFS，判断起点是否为老鼠胜
        return calc(gMouse, gCat, mouseStart, catStart, food) == 1;  // 结论 1 表示老鼠胜，转成 bool 返回
    }  // canMouseWin 结束
};  // 类结束
