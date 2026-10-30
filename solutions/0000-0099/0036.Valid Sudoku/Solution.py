# 题目：36. 有效的数独（Valid Sudoku）
# 思路：一次遍历 81 格，用 row/col/sub 三组布尔表分别标记第 i 行、第 j 列、第 k 个 3×3 宫是否已出现数字 v；任何一处重复即判无效。
# 时间复杂度：O(1)（棋盘固定 9×9）；空间复杂度：O(1)，三张 9×9 的布尔表。
class Solution:  # LeetCode 约定的题解类
    def isValidSudoku(self, board: List[List[str]]) -> bool:  # board 是 9×9 字符棋盘，'.' 表示空格；判断已填数字是否违反数独规则
        row = [[False] * 9 for _ in range(9)]  # 行表：row[i][v] 表示第 i 行是否已出现数字 v+1；每行用独立列表推导生成，避免九行共享同一个对象
        col = [[False] * 9 for _ in range(9)]  # col[j][v] 表示第 j 列是否已出现数字 v+1；同样用推导式生成九个独立列表
        sub = [[False] * 9 for _ in range(9)]  # 宫表：sub[k][v] 表示第 k 个 3×3 宫是否已出现数字 v+1
        for i in range(9):  # 枚举每一行
            for j in range(9):  # 枚举每一列，逐格扫描棋盘
                c = board[i][j]  # 取出当前格子的字符
                if c == '.':  # 空格没有数字，跳过即可，不参与冲突检查
                    continue  # 直接进入下一格，continue 会跳过本轮的后续判断
                num = int(c) - 1  # 把字符数字转成 0..8 的下标：'1' 对应 0，'9' 对应 8
                k = i // 3 * 3 + j // 3  # 行列坐标映射到 0..8 的宫编号：i//3 是宫的行号，j//3 是宫的列号
                if row[i][num] or col[j][num] or sub[k][num]:  # 行、列、宫任意一处已出现过该数字，就说明数独无效
                    return False  # 发现冲突立即返回 False，不用继续检查
                row[i][num] = True  # 标记该数字已在本行出现
                col[j][num] = True  # 标记该数字已在本列出现
                sub[k][num] = True  # 标记该数字已在本宫出现
        return True  # 81 格全部扫完且没有冲突，返回 True
