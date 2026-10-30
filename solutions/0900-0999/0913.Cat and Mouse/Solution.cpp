// 题目：913. 猫和老鼠（Cat and Mouse）
// 核心思路：博弈论 + 反向拓扑 BFS。从已知终局（猫进洞判鼠胜、猫抓到鼠判猫胜）出发，反向推导每个状态：若某前驱存在一步直接走向自己的胜利，则它必胜；否则不断消耗它的出边计数，计数归零说明所有走法都输，则它必败。
// 时间复杂度：O(n^3)，状态数 O(n^2)、每条边只被松弛一次；空间复杂度：O(n^2)，保存 ans 与 degree 两个三维数组。
const int HOLE = 0;  // 洞的编号固定为 0
const int MOUSE_START = 1;  // 老鼠起点编号为 1
const int CAT_START = 2;  // 猫的起点编号为 2
const int MOUSE_TURN = 0;  // 用 0 表示轮到老鼠走
const int CAT_TURN = 1;  // 用 1 表示轮到猫走
const int MOUSE_WIN = 1;  // 状态结果：老鼠胜
const int CAT_WIN = 2;  // 状态结果：猫胜
const int TIE = 0;  // 状态结果：平局（也是「尚未确定」的初值）

class Solution {  // 题解类
public:  // 对外接口
    int catMouseGame(vector<vector<int>>& graph) {  // graph：无向图邻接表；返回 1 鼠胜、2 猫胜、0 平局
        int n = graph.size();  // 节点个数（节点 0 是洞）
        int ans[n][n][2];  // ans[m][c][t]：鼠在 m、猫在 c、轮到 t 方走时的结果，0 表示尚未确定
        int degree[n][n][2];  // degree[m][c][t]：该状态还有多少条出边没有被判定为「对行动方不利」
        memset(ans, 0, sizeof ans);  // 初始全部置 0，即所有状态先按未知处理
        memset(degree, 0, sizeof degree);  // 度数也先清零，随后按图结构逐项填充
        for (int i = 0; i < n; ++i) {  // 遍历老鼠可能所在的位置 i
            for (int j = 1; j < n; ++j) {  // 遍历猫可能所在的位置 j；猫不会在洞里，所以从 1 开始
                degree[i][j][MOUSE_TURN] = graph[i].size();  // 轮老鼠走时，出边数就是老鼠所在点的度数
                degree[i][j][CAT_TURN] = graph[j].size();  // 轮猫走时，出边数就是猫所在点的度数
            }  // 内层位置遍历结束
            for (int j : graph[HOLE]) {  // 猫不能走进洞，需要把这些非法出边从计数里扣除
                --degree[i][j][CAT_TURN];  // 洞的邻居 j 作为猫的位置时，少了一条「走进洞」的边
            }  // 非法边扣除结束
        }  // 所有状态的初始度数填充完毕
        auto getPrevStates = [&](int m, int c, int t) {  // 辅助 lambda：求状态 (m, c, t) 的全部前驱状态，用于反向 BFS
            int pt = t ^ 1;  // 前驱是上一回合，所以行动方要取反（异或 1 在 0/1 之间切换）
            vector<tuple<int, int, int>> pre;  // 存放前驱状态 (前驱鼠位置, 前驱猫位置, 前驱行动方)
            if (pt == CAT_TURN) {  // 前驱由猫行动，说明猫是从某个邻居 pc 走到 c 的
                for (int pc : graph[c]) {  // 枚举猫所有可能的上一位置
                    if (pc != HOLE) {  // 猫不可能待在洞里，非法前驱直接跳过
                        pre.emplace_back(m, pc, pt);  // 记录这个合法前驱
                    }  // 合法性判断结束
                }  // 猫的前驱位置枚举结束
            } else {  // 否则前驱由老鼠行动，老鼠是从某个邻居 pm 走到 m 的
                for (int pm : graph[m]) {  // 枚举老鼠所有可能的上一位置
                    pre.emplace_back(pm, c, pt);  // 老鼠可以待在洞里，所以无需过滤
                }  // 老鼠的前驱位置枚举结束
            }  // 分支结束
            return pre;  // 返回全部前驱状态
        };  // lambda 定义结束
        queue<tuple<int, int, int>> q;  // 反向 BFS 队列，初始装入的都是结果已确定的状态
        for (int j = 1; j < n; ++j) {  // 终局一：老鼠在洞里，无论轮到谁走都是老鼠胜
            ans[0][j][MOUSE_TURN] = ans[0][j][CAT_TURN] = MOUSE_WIN;  // 两种轮次的结果一起标记为老鼠胜
            q.emplace(0, j, MOUSE_TURN);  // 轮老鼠走的状态入队，作为反向推导起点
            q.emplace(0, j, CAT_TURN);  // 轮猫走的状态同样入队
        }  // 终局一初始化结束
        for (int i = 1; i < n; ++i) {  // 终局二：猫和老鼠同处一个非洞节点，猫立刻抓住老鼠
            ans[i][i][MOUSE_TURN] = ans[i][i][CAT_TURN] = CAT_WIN;  // 两种轮次的结果一起标记为猫胜
            q.emplace(i, i, MOUSE_TURN);  // 轮老鼠走的状态入队
            q.emplace(i, i, CAT_TURN);  // 轮猫走的状态入队
        }  // 终局二初始化结束
        while (!q.empty()) {  // 反向 BFS：把已确定的结果不断传播给前驱状态
            auto [m, c, t] = q.front();  // 取出队首状态，用结构化绑定拆成三个维度
            q.pop();  // 弹出队首
            int x = ans[m][c][t];  // 该状态已经确定的结果
            for (auto [pm, pc, pt] : getPrevStates(m, c, t)) {  // 遍历所有能一步走到当前状态的前驱
                if (ans[pm][pc][pt] == TIE) {  // 只处理结果尚未确定的前驱
                    bool win = (x == MOUSE_WIN && pt == MOUSE_TURN) || (x == CAT_WIN && pt == CAT_TURN);  // 轮到该行动方走、且结果是该行动方获胜，则前驱可以直接取胜
                    if (win) {  // 前驱存在一步走向自己胜利的走法
                        ans[pm][pc][pt] = x;  // 立即判定前驱为胜（胜局优先于其它分支）
                        q.emplace(pm, pc, pt);  // 入队，继续向前传播
                    } else {  // 否则这条边对前驱的行动方不利，消耗它一次选择机会
                        if (--degree[pm][pc][pt] == 0) {  // 可选走法减一，减到 0 说明所有走法都会输
                            ans[pm][pc][pt] = x;  // 前驱必败，结果与后继相同
                            q.emplace(pm, pc, pt);  // 入队，继续向前传播
                        }  // 必败判断结束
                    }  // 胜负分支结束
                }  // 只在未确定时处理，避免重复松弛
            }  // 前驱遍历结束
        }  // BFS 主循环结束
        return ans[MOUSE_START][CAT_START][MOUSE_TURN];  // 初始状态（鼠 1、猫 2、鼠先走）的结果就是答案
    }  // 方法结束
};  // 类定义结束
