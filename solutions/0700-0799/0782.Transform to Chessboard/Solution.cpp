// 题目：782. 变为棋盘（Transform to Chessboard）
// 思路：把每行、每列压成 n 位掩码。合法棋盘要求任意两行（列）要么完全相同、要么互为按位取反，且 1 的个数只能是 ⌊n/2⌋ 或 ⌈n/2⌉。行内交换与列间交换互不影响，所以答案 = 行方向最少交换数 + 列方向最少交换数；每个方向的交换数等于「放在错误奇偶位上的元素个数」。
// 时间复杂度：O(n^2)，需要遍历整个棋盘构造掩码；空间复杂度：O(1)，只用若干 n 位整数与计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int n;  // n：棋盘边长，设为成员变量，方便辅助函数 f 直接使用
    int movesToChessboard(vector<vector<int>>& board) {  // board：0/1 棋盘；返回变成棋盘的最少交换次数，无法做到返回 -1
        n = board.size();  // 记录边长
        int mask = (1 << n) - 1;  // mask：低 n 位全为 1，用来求某个掩码的逐位取反
        int rowMask = 0, colMask = 0;  // rowMask / colMask：第 0 行、第 0 列的位掩码，作为基准形态
        for (int i = 0; i < n; ++i) {  // 逐位构造基准行与基准列的掩码
            rowMask |= board[0][i] << i;  // 把第 0 行第 i 个元素放到第 i 位上
            colMask |= board[i][0] << i;  // 把第 0 列第 i 个元素（board[i][0]）放到第 i 位上
        }
        int revRowMask = mask ^ rowMask;  // 基准行逐位取反，得到棋盘里与它互补的那种行形态
        int revColMask = mask ^ colMask;  // 基准列逐位取反，得到互补的列形态
        int sameRow = 0, sameCol = 0;  // sameRow / sameCol：和基准掩码完全相同（不取反）的行数、列数
        for (int i = 0; i < n; ++i) {  // 逐行、逐列检查合法形态并统计
            int curRowMask = 0, curColMask = 0;  // 当前第 i 行、第 i 列的掩码
            for (int j = 0; j < n; ++j) {  // 逐位构造这两个掩码
                curRowMask |= board[i][j] << j;  // 第 i 行的位掩码
                curColMask |= board[j][i] << j;  // 第 i 列（board[j][i]）的位掩码
            }
            if (curRowMask != rowMask && curRowMask != revRowMask) return -1;  // 出现既不是 rowMask 也不是其取反的行，说明永远变不成棋盘，直接返回 -1
            if (curColMask != colMask && curColMask != revColMask) return -1;  // 列方向的同样检查
            sameRow += curRowMask == rowMask;  // 比较结果为真时值为 1，正好累加出「不取反」的行数
            sameCol += curColMask == colMask;  // 同样累加出「不取反」的列数
        }
        int t1 = f(rowMask, sameRow);  // 行方向排序成棋盘所需的最少交换次数
        int t2 = f(colMask, sameCol);  // 列方向排序成棋盘所需的最少交换次数
        return t1 == -1 || t2 == -1 ? -1 : t1 + t2;  // 任一方向无解则整体 -1，否则行、列次数相加（两种交换互不影响）
    }  // movesToChessboard 方法结束

    int f(int mask, int cnt) {  // 辅助函数：mask 是某个方向的基准掩码，cnt 是与它相同（不取反）的行/列数
        int ones = __builtin_popcount(mask);  // ones：mask 中 1 的个数，即该行/列里 1 的数量
        if (n & 1) {  // 分奇偶讨论：棋盘每行（列）的 1 的个数必须尽量均分
            if (abs(n - ones * 2) != 1 || abs(n - cnt * 2) != 1) return -1;  // 奇数长度时 1 与 0 的个数只能差 1；同理 cnt 与 n-cnt 也必须差 1，否则无解
            if (ones == n / 2) return n / 2 - __builtin_popcount(mask & 0xAAAAAAAA);  // ones 较少（=n/2）时 1 应落在奇数下标位上（0xAAAAAAAA），错位数就是需要交换的次数
            return (n + 1) / 2 - __builtin_popcount(mask & 0x55555555);  // 否则 1 较多，应落在偶数下标位（0x55555555），用占据多数位的个数减去已经就位的个数
        } else {  // 偶数长度分支
            if (ones != n / 2 || cnt != n / 2) return -1;  // 偶数长度要求 1 的个数恰为 n/2，且与 mask 相同的行/列数也恰为 n/2
            int cnt0 = (n / 2 - __builtin_popcount(mask & 0xAAAAAAAA));  // 方案一：让 1 落在奇数下标位（0xAAAAAAAA）时的错位个数
            int cnt1 = (n / 2 - __builtin_popcount(mask & 0x55555555));  // 方案二：让 1 落在偶数下标位（0x55555555）时的错位个数
            return min(cnt0, cnt1);  // 两种摆放都可行，取交换次数较少的那个
        }
    }  // f 函数结束
};  // Solution 类定义结束