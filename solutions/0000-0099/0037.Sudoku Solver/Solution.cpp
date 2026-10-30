// 题目：37. 解数独（Sudoku Solver）
// 思路：先把所有空格按行优先顺序收进序列 t，并用 row/col/block 三张布尔表记录已用数字；再按 t 的顺序回溯 DFS，每格试 1..9，填满即得到解。
// 时间复杂度：最坏 O(9^m)（m 为空格数），实际被冲突剪枝大幅削减；空间复杂度：O(m)，递归深度与空格数同阶，三张表为常数大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void solveSudoku(vector<vector<char>>& board) {  // board 是 9×9 棋盘，'.' 表示空格；原地填满棋盘，函数无返回值
        bool row[9][9] = {false};  // row[i][v]：第 i 行是否已经用了数字 v+1
        bool col[9][9] = {false};  // col[j][v]：第 j 列是否已经用了数字 v+1
        bool block[3][3][9] = {false};  // block[x][y][v]：第 (x,y) 个 3×3 宫是否已经用了数字 v+1
        bool ok = false;  // 找到解后置为 true，让各层递归尽快收敛退出
        vector<pair<int, int>> t;  // 按行优先顺序保存所有空格坐标，DFS 就按这个顺序逐格填数
        for (int i = 0; i < 9; ++i) {  // 枚举行
            for (int j = 0; j < 9; ++j) {  // 枚举列，逐格扫描棋盘
                if (board[i][j] == '.') {  // 遇到空格，先记下坐标，留到回溯阶段再填
                    t.push_back({i, j});  // 保存该空格的 (行, 列)
                } else {  // 否则这个格子是题面已给的数字，需要先登记进三张表
                    int v = board[i][j] - '1';  // 把字符数字转成 0..8 的下标
                    row[i][v] = col[j][v] = block[i / 3][j / 3][v] = true;  // 一条链式赋值同时把该数字登记到行、列、宫三张表，省去重复代码
                }  // else 分支结束
            }  // 内层 for 结束
        }  // 外层 for 结束，此时棋盘上的已知数字都已登记完毕
        auto dfs = [&](this auto&& dfs, int k) -> void {  // 回溯函数：k 是当前要填第 k 个空格；C++23 的 this auto&& dfs 让 lambda 能递归调用自己
            if (k == t.size()) {  // 空格全部填完，说明找到了一组完整解
                ok = true;  // 打上成功标记，供上层判断
                return;  // 结束本层递归
            }  // if 分支结束
            int i = t[k].first, j = t[k].second;  // 取出第 k 个空格的行列坐标
            for (int v = 0; v < 9; ++v) {  // 依次尝试数字 1..9（下标 0..8）
                if (!row[i][v] && !col[j][v] && !block[i / 3][j / 3][v]) {  // 只有行、列、宫都没用过该数字时才可以尝试，这就是剪枝条件
                    row[i][v] = col[j][v] = block[i / 3][j / 3][v] = true;  // 做选择：先把该数字登记进三张表
                    board[i][j] = v + '1';  // 把数字真正写进棋盘（下标 0 对应字符 '1'）
                    dfs(k + 1);  // 递归填下一个空格
                    row[i][v] = col[j][v] = block[i / 3][j / 3][v] = false;  // 回溯：撤销登记，让同层其他数字分支可以继续使用
                }  // if 分支（尝试某个数字）结束
                if (ok) {  // 一旦已经找到解，本格就不必再试其他数字
                    return;  // 逐层返回，把成功的信号传上去
                }  // if (ok) 结束
            }  // for 结束
        };  // lambda 定义结束
        dfs(0);  // 从第 0 个空格开始回溯，函数返回时棋盘已被原地填满
    }  // 方法结束
};  // 类定义结束
