// 题目：36. 有效的数独（Valid Sudoku）
// 思路：一次遍历 81 格，用 row/col/sub 三组布尔表分别标记第 i 行、第 j 列、第 k 个 3×3 宫是否已出现过数字 v；任何一处重复即判无效。
// 时间复杂度：O(1)（棋盘固定 9×9，共 81 格）；空间复杂度：O(1)，三张 9×9 的布尔表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isValidSudoku(vector<vector<char>>& board) {  // board 是 9×9 字符棋盘，'.' 表示空格；判断已填好的数字是否违反数独规则
        vector<vector<bool>> row(9, vector<bool>(9, false));  // row[i][v] 表示第 i 行是否已出现数字 v+1（下标 0..8 对应数字 1..9）
        vector<vector<bool>> col(9, vector<bool>(9, false));  // col[j][v] 表示第 j 列是否已出现数字 v+1
        vector<vector<bool>> sub(9, vector<bool>(9, false));  // sub[k][v] 表示第 k 个 3×3 宫是否已出现数字 v+1
        for (int i = 0; i < 9; ++i) {  // 枚举每一行
            for (int j = 0; j < 9; ++j) {  // 枚举每一列，逐格扫描棋盘
                char c = board[i][j];  // 取出当前格子的字符
                if (c == '.') continue;  // 空格没有数字，直接跳过，不参与冲突检查
                int num = c - '0' - 1;  // 字符数字转成 0..8 的下标：'1' 对应 0，'9' 对应 8
                int k = i / 3 * 3 + j / 3;  // 把行列坐标映射到 0..8 的宫编号：i/3 是宫的行号，j/3 是宫的列号
                if (row[i][num] || col[j][num] || sub[k][num]) {  // 行、列、宫中任意一处已出现过该数字，说明数独无效
                    return false;  // 发现冲突立刻返回 false，无需继续检查
                }  // if 分支结束
                row[i][num] = true;  // 标记该数字已在本行出现
                col[j][num] = true;  // 标记该数字已在本列出现
                sub[k][num] = true;  // 标记该数字已在本宫出现
            }  // 内层 for 结束
        }  // 外层 for 结束
        return true;  // 81 格全部扫完且没有冲突，说明数独有效
    }  // 方法结束
};  // 类定义结束
