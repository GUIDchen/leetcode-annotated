// 题目：1812. 判断国际象棋棋盘中一个格子的颜色（Determine Color of a Chessboard Square）
// 思路：棋盘上同色格子的「列字母 + 行数字」奇偶性相同，直接看两字符 ASCII 码之和是否为奇数即可。
// 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool squareIsWhite(string coordinates) {  // coordinates：形如 e4 的两字符坐标，下标 0 是列字母、下标 1 是行数字
        return (coordinates[0] + coordinates[1]) % 2;  // 两字符 ASCII 码之和模 2 得 1 即为白格，非零自动转成 true
    }  // 方法结束
};  // 类定义结束