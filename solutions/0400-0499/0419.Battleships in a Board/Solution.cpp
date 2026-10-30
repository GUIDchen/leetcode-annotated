// 题目：419. 棋盘上的战舰（Battleships in a Board）
// 思路：只统计每艘战舰的「左上端」——当前格是 'X' 且上方、左方都不是 'X'，它就是这艘战舰的第一格，计数一次。
// 时间复杂度：O(m * n)，只扫一遍棋盘；空间复杂度：O(1)，只用了几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countBattleships(vector<vector<char>>& board) {  // board 是 'X'（战舰）与 '.'（空）组成的棋盘，返回战舰数量
        int m = board.size(), n = board[0].size();  // m 行、n 列
        int ans = 0;  // ans 记录战舰数量
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                if (board[i][j] == '.') {  // 空格直接跳过
                    continue;  // 继续检查下一格
                }  // 空格分支结束
                if (i > 0 && board[i - 1][j] == 'X') {  // 上方也是 'X'，说明当前格是某艘纵向战舰的中间或尾部，不能重复计数
                    continue;  // 跳过，避免一艘战舰被数多次
                }  // 纵向判断结束
                if (j > 0 && board[i][j - 1] == 'X') {  // 左方也是 'X'，说明当前格是某艘横向战舰的中间或尾部
                    continue;  // 跳过，避免重复计数
                }  // 横向判断结束
                ++ans;  // 上方、左方都不是 'X'，当前格是一艘新战舰的左上端，计数加一
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回战舰总数
    }  // countBattleships 方法结束
};  // Solution 类结束