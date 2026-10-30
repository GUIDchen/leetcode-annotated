// 题目：773. 滑动谜题（Sliding Puzzle）
// 核心思路：把 2×3 局面编码成 6 位字符串，从初始局面做 BFS，逐层扩展 0 与上下左右交换后的新局面，首次遇到目标串即最少步数。
// 时间复杂度 O(6!·6)，状态数最多 720 个；空间复杂度 O(6!)，用于 visited 集合与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对判题器可见
    int slidingPuzzle(vector<vector<int>>& board) {  // board：2×3 的初始棋盘；返回还原为目标串的最少移动次数，无解返回 -1
        string start = gets(board);  // 把二维棋盘编码成 6 位字符串，作为 BFS 的状态
        string end = "123450";  // 目标状态：0 在右下角，其余按 1 到 5 顺序排列
        if (start == end) return 0;  // 开局就是目标状态，答案为 0 步
        unordered_set<string> vis;  // 访问集合：记录已入队过的状态，避免重复搜索
        vis.insert(start);  // 起点标记为已访问
        queue<string> q{{start}};  // BFS 队列，初始只放入起点
        int ans = 0;  // ans 记录已经走过的步数
        while (!q.empty()) {  // 队列非空就继续一层层扩展
            ++ans;  // 进入新的一层，步数加一
            for (int n = q.size(); n > 0; --n) {  // 只弹出当前层的 q.size() 个状态，保证 ans 与层数同步
                string x = q.front();  // 取出队首状态字符串
                q.pop();  // 出队
                setb(x, board);  // 把字符串还原成二维棋盘，供下面的后继生成函数使用
                for (string y : next(board)) {  // 枚举 0 与四个方向交换后的所有后继状态
                    if (y == end) return ans;  // 一步就到达目标，当前层数就是答案
                    if (!vis.count(y)) {  // 后继状态没访问过才入队
                        vis.insert(y);  // 标记为已访问
                        q.push(y);  // 加入队列，等下一层扩展
                    }  // if 结束
                }  // 内层 for 结束
            }  // 外层 for 结束
        }  // while 结束
        return -1;  // 状态全部搜完仍未到达目标，返回 -1 表示无解
    }  // 方法结束

    string gets(vector<vector<int>>& board) {  // 把二维棋盘按行优先编码成 6 位字符串
        string s = "";  // 结果字符串，逐位追加
        for (int i = 0; i < 2; ++i)  // 枚举两行
            for (int j = 0; j < 3; ++j)  // 枚举三列（按行优先顺序写入）
                s.push_back('0' + board[i][j]);  // 数字 0 到 5 转成对应字符追加，编码位置为 i*3+j
        return s;  // 返回编码后的状态字符串
    }  // gets 结束

    void setb(string s, vector<vector<int>>& board) {  // 把 6 位字符串状态还原写回二维棋盘
        for (int i = 0; i < 2; ++i)  // 枚举两行
            for (int j = 0; j < 3; ++j)  // 枚举三列
                board[i][j] = s[i * 3 + j] - '0';  // 字符减字符零还原成数字，写回第 i 行第 j 列
    }  // setb 结束

    vector<string> next(vector<vector<int>>& board) {  // 生成 0 与上下左右四个方向交换后的全部后继状态
        vector<string> res;  // 存放后继状态编码
        auto p = find0(board);  // 找到数字 0 当前所在的行列
        int i = p.first, j = p.second;  // 拆出 0 的行 i 与列 j
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组：上、右、下、左的（行增量, 列增量），成对读取
        for (int k = 0; k < 4; ++k) {  // 枚举四个方向
            int x = i + dirs[k], y = j + dirs[k + 1];  // 计算交换目标格的行 x、列 y
            if (x >= 0 && x < 2 && y >= 0 && y < 3) {  // 目标格必须落在 2×3 棋盘范围内
                swap(i, j, x, y, board);  // 交换 0 与目标格，得到候选局面
                res.push_back(gets(board));  // 编码候选局面并加入结果
                swap(i, j, x, y, board);  // 再交换一次把棋盘还原，避免影响下一个方向
            }  // if 结束
        }  // for 结束
        return res;  // 返回所有后继状态
    }  // next 结束

    void swap(int i, int j, int x, int y, vector<vector<int>>& board) {  // 交换棋盘上 (i, j) 与 (x, y) 两格的数字
        int t = board[i][j];  // 暂存第一格的数字
        board[i][j] = board[x][y];  // 第二格覆盖第一格
        board[x][y] = t;  // 暂存值写回第二格，完成交换
    }  // swap 结束

    pair<int, int> find0(vector<vector<int>>& board) {  // 查找数字 0 在棋盘上的位置
        for (int i = 0; i < 2; ++i)  // 枚举行
            for (int j = 0; j < 3; ++j)  // 枚举列
                if (board[i][j] == 0)  // 找到 0 就立刻返回它的坐标
                    return {i, j};  // 返回 {行, 列}
        return {0, 0};  // 理论上不会走到这里，返回 {0, 0} 只为满足函数返回值要求
    }  // find0 结束
};  // 类定义结束