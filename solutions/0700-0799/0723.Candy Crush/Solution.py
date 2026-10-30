# 题目：723. 粉碎糖果（Candy Crush，会员题）
# 思路：直接模拟。每轮先用负数标记水平/竖直三连（只标记不清零，避免同一轮重复判断），再让每列糖果下落，直到没有可消除为止。
# 时间复杂度：O(m*n*(m+n))（轮数与棋盘同阶，每轮 O(m*n)）；空间复杂度：O(1)（原地修改，不计返回值）。
class Solution:  # LeetCode 约定的题解类
    def candyCrush(self, board: List[List[int]]) -> List[List[int]]:  # board：糖果棋盘，0 表示空位
        m, n = len(board), len(board[0])  # 行数与列数
        run = True  # 本轮是否发生过消除
        while run:  # 反复执行「标记 → 下落」直到稳定
            run = False  # 先假设本轮不会消除
            for i in range(m):  # 逐行扫描水平方向的三连
                for j in range(2, n):  # 以 j 为三连的最右端点枚举
                    if board[i][j] and abs(board[i][j]) == abs(board[i][j - 1]) == abs(  # 非空且连续三格值相同（abs 兼容负标记），条件跨行书写
                        board[i][j - 2]  # 三连的最左元素（续行）
                    ):  # 条件表达式结束
                        run = True  # 记录本轮发生了消除
                        board[i][j] = board[i][j - 1] = board[i][j - 2] = -abs(  # 用负值标记待消除，先标记不清零，避免影响本轮后续判断
                            board[i][j]  # 标记的取值来自当前格（续行）
                        )  # 链式赋值结束
            for j in range(n):  # 逐列扫描竖直方向的三连
                for i in range(2, m):  # 以 i 为三连的最下端点枚举
                    if board[i][j] and abs(board[i][j]) == abs(board[i - 1][j]) == abs(  # 同列连续三格值相同（条件跨行书写）
                        board[i - 2][j]  # 三连的最上元素（续行）
                    ):  # 条件表达式结束
                        run = True  # 记录本轮发生了消除
                        board[i][j] = board[i - 1][j] = board[i - 2][j] = -abs(  # 用负值标记待消除
                            board[i][j]  # 标记的取值（续行）
                        )  # 链式赋值结束
            if run:  # 本轮有消除，需要整理下落
                for j in range(n):  # 逐列处理下落
                    k = m - 1  # k 指向当前最低的空位
                    for i in range(m - 1, -1, -1):  # 自底向上遍历该列
                        if board[i][j] > 0:  # 正数才是未被消除的糖果
                            board[k][j] = board[i][j]  # 糖果落到当前最低的空位
                            k -= 1  # 放置位置上移
                    while k >= 0:  # 剩余上方位置全部清空
                        board[k][j] = 0  # 置 0 表示空位
                        k -= 1  # 继续向上清空
        return board  # 返回稳定后的棋盘
