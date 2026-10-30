# 题目：782. 变为棋盘（Transform to Chessboard）
# 思路：把每行、每列压成 n 位掩码。合法棋盘要求任意两行（列）要么相同、要么互为按位取反，且 1 的个数只能是 ⌊n/2⌋ 或 ⌈n/2⌉。行列交换互不影响，答案是两方向的最少交换数之和，每个方向的交换数等于「放在错误奇偶位上的元素个数」。
# 时间复杂度：O(n^2)，需要遍历整个棋盘构造掩码；空间复杂度：O(1)，只用若干整数与计数器。
class Solution:  # LeetCode 约定的题解类
    def movesToChessboard(self, board: List[List[int]]) -> int:  # board：0/1 棋盘；返回变成棋盘的最少交换次数，无法做到返回 -1
        def f(mask, cnt):  # 嵌套函数 f：mask 是某方向的基准掩码，cnt 是与它相同（不取反）的行/列数
            ones = mask.bit_count()  # ones：mask 中 1 的个数（bit_count 统计二进制 1 的位数）
            if n & 1:  # n 为奇数时，1 与 0 的个数只能差 1
                if abs(n - 2 * ones) != 1 or abs(n - 2 * cnt) != 1:  # |n-2*ones| 必须为 1；行、列的不取反个数 cnt 同理，否则无解
                    return -1  # 返回 -1 表示该方向无解
                if ones == n // 2:  # ones 较少（=n/2）：1 应落在奇数下标位，错位数就是最少交换数
                    return n // 2 - (mask & 0xAAAAAAAA).bit_count()  # 0xAAAAAAAA 选出奇数下标位，n//2 减去已就位的 1 的个数
                return (n + 1) // 2 - (mask & 0x55555555).bit_count()  # 否则 1 较多：应落在偶数下标位 (n+1)//2 - 已就位个数
            else:  # n 为偶数的分支
                if ones != n // 2 or cnt != n // 2:  # 偶数长度要求 1 的个数恰为 n/2，且与 mask 相同的行/列数也恰为 n/2
                    return -1  # 无解
                cnt0 = n // 2 - (mask & 0xAAAAAAAA).bit_count()  # 方案一：让 1 落在奇数下标位（0xAAAAAAAA）时的错位个数
                cnt1 = n // 2 - (mask & 0x55555555).bit_count()  # 方案二：让 1 落在偶数下标位（0x55555555）时的错位个数
                return min(cnt0, cnt1)  # 两种摆放都可行，取较小的交换次数

        n = len(board)  # n：棋盘边长；后面 f 只在被调用时读取它，闭包能取到此时赋的值
        mask = (1 << n) - 1  # mask：低 n 位全 1，用来求逐位取反
        rowMask = colMask = 0  # rowMask / colMask：第 0 行、第 0 列的位掩码，作为基准形态
        for i in range(n):  # 逐位构造基准行与基准列
            rowMask |= board[0][i] << i  # 第 0 行第 i 个元素放到第 i 位
            colMask |= board[i][0] << i  # 第 0 列第 i 个元素放到第 i 位
        revRowMask = mask ^ rowMask  # 基准行逐位取反，得到互补的行形态
        revColMask = mask ^ colMask  # 基准列逐位取反，得到互补的列形态
        sameRow = sameCol = 0  # sameRow / sameCol：与基准掩码完全相同（不取反）的行数、列数
        for i in range(n):  # 逐行、逐列检查并统计
            curRowMask = curColMask = 0  # 第 i 行、第 i 列的掩码
            for j in range(n):  # 逐位构造这两个掩码
                curRowMask |= board[i][j] << j  # 第 i 行的位掩码
                curColMask |= board[j][i] << j  # 第 i 列（board[j][i]）的位掩码
            if curRowMask not in (rowMask, revRowMask) or curColMask not in (  # 只要不是「基准」或「基准取反」两种形态，就永远变不成棋盘
                colMask,  # 允许的列形态之一：与基准列 colMask 完全相同
                revColMask,  # 允许的另一种列形态：基准列的逐位取反
            ):  # 元组结束
                return -1  # 返回 -1 表示该棋盘无法通过交换变成棋盘，直接失败
            sameRow += curRowMask == rowMask  # 比较结果为 True/False，参与加法时按 1/0 累加「不取反」的行数
            sameCol += curColMask == colMask  # 同样累加「不取反」的列数
        t1 = f(rowMask, sameRow)  # 行方向所需的最少交换次数
        t2 = f(colMask, sameCol)  # 列方向所需的最少交换次数
        return -1 if t1 == -1 or t2 == -1 else t1 + t2  # 任一方向无解则为 -1，否则两个方向的次数相加
