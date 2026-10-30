// 题目：3274. 检查棋盘方格颜色是否相同（Check if Two Chessboard Squares Have the Same Color）
// 思路：棋盘颜色由列字母与行号的奇偶性共同决定，两格的列差与行差之和为偶数时颜色相同。
// 时间复杂度：O(1)，只做常数次字符运算；空间复杂度：O(1)，只用两个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkTwoChessboards(string coordinate1, string coordinate2) {  // coordinate1、coordinate2：形如 "a1" 的坐标
        int x = coordinate1[0] - coordinate2[0];  // 列字母的 ASCII 差，其奇偶性等价于列号之差的奇偶性
        int y = coordinate1[1] - coordinate2[1];  // 行号的差值
        return (x + y) % 2 == 0;  // 列差与行差之和为偶数，说明两格颜色相同
    }
};
