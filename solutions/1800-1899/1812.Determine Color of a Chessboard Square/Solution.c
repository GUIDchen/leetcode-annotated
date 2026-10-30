// 题目：1812. 判断国际象棋棋盘中一个格子的颜色（Determine Color of a Chessboard Square）
// 思路：棋盘上同色格子的「列字母 + 行数字」奇偶性相同，直接取两字符 ASCII 码之和的最低位判断即可。
// 时间复杂度：O(1)；空间复杂度：O(1)。
bool squareIsWhite(char* coordinates) {  // coordinates 是形如 e4 的两字符坐标：第 0 位是列字母，第 1 位是行数字
    return (coordinates[0] + coordinates[1]) & 1;  // 行列下标之和为奇数即白格；与 1 相与取出最低位，1 表示白、0 表示黑
}  // 函数结束