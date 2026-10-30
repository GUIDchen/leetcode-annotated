# 题目：1895. 最大的幻方（Largest Magic Square）
# 思路：先预处理行、列方向前缀和，使子方阵的每行和、每列和都能 O(1) 得到；再从大到小枚举边长与左上角，用嵌套函数 check 校验行、列、两条对角线是否同和。
# 时间复杂度：O(mn·min(m,n))；空间复杂度：O(mn)，两份前缀和表。
class Solution:  # LeetCode 约定的题解类
    def largestMagicSquare(self, grid: List[List[int]]) -> int:  # grid：输入的整数矩阵，返回内部最大的幻方边长
        m, n = len(grid), len(grid[0])  # 矩阵的行数 m 与列数 n
        rowsum = [[0] * (n + 1) for _ in range(m + 1)]  # 行方向前缀和：rowsum[i][j] = grid 第 i-1 行前 j 个元素之和（多一行一列便于递推）
        colsum = [[0] * (n + 1) for _ in range(m + 1)]  # 列方向前缀和：colsum[i][j] = grid 第 j-1 列前 i 个元素之和
        for i in range(1, m + 1):  # i 从 1 开始，对应 grid 的第 i-1 行
            for j in range(1, n + 1):  # j 从 1 开始，对应 grid 的第 j-1 列
                rowsum[i][j] = rowsum[i][j - 1] + grid[i - 1][j - 1]  # 本行区间和 = 本行前一列前缀 + 当前格子
                colsum[i][j] = colsum[i - 1][j] + grid[i - 1][j - 1]  # 本列区间和 = 上一行同列前缀 + 当前格子
  # 空行：分隔前缀和预处理与嵌套判定函数
        def check(x1, y1, x2, y2):  # check：判断 (x1,y1) 到 (x2,y2) 的子方阵是否所有行、列、对角线和相等
            val = rowsum[x1 + 1][y2 + 1] - rowsum[x1 + 1][y1]  # 以第一行的行和为基准值 val
            for i in range(x1 + 1, x2 + 1):  # 从第二行开始逐行比对
                if rowsum[i + 1][y2 + 1] - rowsum[i + 1][y1] != val:  # 行和不等就说明不是幻方
                    return False  # 返回 False
            for j in range(y1, y2 + 1):  # 逐列比对列和
                if colsum[x2 + 1][j + 1] - colsum[x1][j + 1] != val:  # 列和不等就说明不是幻方
                    return False  # 返回 False
            s, i, j = 0, x1, y1  # s 累计主对角线和；i、j 从左上角出发（链式赋值一次设三个变量）
            while i <= x2:  # 沿主对角线走到右下角
                s += grid[i][j]  # 累加对角线元素
                i += 1  # 行下标下移
                j += 1  # 列下标右移
            if s != val:  # 主对角线和必须等于基准值
                return False  # 返回 False
            s, i, j = 0, x1, y2  # 重新初始化，准备统计副对角线
            while i <= x2:  # 沿副对角线从右上走到左下
                s += grid[i][j]  # 累加对角线元素
                i += 1  # 行下标下移
                j -= 1  # 列下标左移
            if s != val:  # 副对角线和必须等于基准值
                return False  # 返回 False
            return True  # 行列与两条对角线全部相等，确认是幻方
  # 空行：分隔嵌套函数与主流程
        for k in range(min(m, n), 1, -1):  # 边长从 min(m, n) 递减到 2，从大到小保证首个命中即最大
            i = 0  # 子方阵左上角行下标从 0 开始
            while i + k - 1 < m:  # 行方向还未越界时继续枚举
                j = 0  # 每换一行，列下标要从 0 重新开始
                while j + k - 1 < n:  # 列方向还未越界时继续枚举
                    i2, j2 = i + k - 1, j + k - 1  # 算出右下角坐标
                    if check(i, j, i2, j2):  # 校验当前 k x k 子方阵
                        return k  # 是幻方就立刻返回当前边长
                    j += 1  # 列下标右移
                i += 1  # 行下标下移，继续找下一行
        return 1  # 边长 1 的方阵总是幻方，作为兜底答案
