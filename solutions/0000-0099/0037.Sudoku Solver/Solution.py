# 题目：37. 解数独（Sudoku Solver）
# 思路：先把所有空格按行优先顺序收进列表 t，并用 row/col/block 三张布尔表记录已用数字；再按 t 的顺序回溯 DFS，每格试 1..9，填满即得到解。
# 时间复杂度：最坏 O(9^m)（m 为空格数），实际被冲突剪枝大幅削减；空间复杂度：O(m)，递归深度与空格数同阶，三张表为常数大小。
class Solution:  # LeetCode 约定的题解类
    def solveSudoku(self, board: List[List[str]]) -> None:  # board 是 9×9 字符棋盘，'.' 表示空格；原地修改棋盘，函数返回 None
        def dfs(k):  # 内部回溯函数：k 是当前要填第 k 个空格，定义在外层方法里以便直接读改写外层变量
            nonlocal ok  # 声明 ok 来自外层作用域：内层函数给 ok 赋值时必须用 nonlocal，否则会新建局部变量
            if k == len(t):  # 空格已全部填完，说明找到一组完整解
                ok = True  # 置成功标记 True
                return  # 结束本层递归
            i, j = t[k]  # 取出第 k 个空格的行列坐标
            for v in range(9):  # 依次尝试数字 1..9（即 v+1 的 v 取 0..8）
                if row[i][v] == col[j][v] == block[i // 3][j // 3][v] == False:  # 链式比较：行、列、宫三张表都为 False 才说明该数字可用
                    row[i][v] = col[j][v] = block[i // 3][j // 3][v] = True  # 做选择：把该数字登记进行、列、宫三张表
                    board[i][j] = str(v + 1)  # 把数字真正写进棋盘，str(v+1) 把 1..9 转成字符
                    dfs(k + 1)  # 递归填下一个空格
                    row[i][v] = col[j][v] = block[i // 3][j // 3][v] = False  # 回溯：撤销登记，让同层其他数字分支能继续尝试
                if ok:  # 若上层已经找到解
                    return  # 立即返回，不再试本格剩下的数字

        row = [[False] * 9 for _ in range(9)]  # 行表：row[i][v] 表示第 i 行是否已用了数字 v+1；用推导式保证九行是九个独立列表
        col = [[False] * 9 for _ in range(9)]  # col[j][v] 表示第 j 列是否已用了数字 v+1；同样用推导式生成九个独立列表
        block = [[[False] * 9 for _ in range(3)] for _ in range(3)]  # 宫表：三维表 block[x][y][v]，表示第 (x,y) 个 3×3 宫是否已用了数字 v+1
        t = []  # 按行优先顺序保存所有空格坐标
        ok = False  # 成功标记：找到解后置为 True（dfs 里通过 nonlocal 修改它）
        for i in range(9):  # 枚举行
            for j in range(9):  # 枚举列，逐格扫描棋盘
                if board[i][j] == '.':  # 遇到空格，先记下坐标，留到回溯阶段再填
                    t.append((i, j))  # 把该空格的 (行, 列) 追加到列表末尾
                else:  # 否则是题面已给的数字，需要先登记进三张表
                    v = int(board[i][j]) - 1  # 把字符数字转成 0..8 的下标
                    row[i][v] = col[j][v] = block[i // 3][j // 3][v] = True  # 链式赋值同时登记到行、列、宫三张表
        dfs(0)  # 从第 0 个空格开始回溯，函数返回时棋盘已被原地填满
