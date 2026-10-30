# 题目：3078. 矩阵中的字母数字模式匹配 I（Match Alphanumerical Pattern in Matrix I）🔒
# 思路：枚举所有可能的左上角，逐格校验 pattern 与 board 子矩阵：数字必须完全相同，字母则维护「字母→数字」和「数字→字母」双向映射保证一一对应。
# 时间复杂度：O(m * n * r * c)，每个候选位置检查一次模式大小；空间复杂度：O(r * c)，映射字典。
class Solution:  # LeetCode 约定的题解类
    def findPattern(self, board: List[List[int]], pattern: List[str]) -> List[int]:  # board：数字矩阵；pattern：数字与字母组成的模式；返回匹配子矩阵的左上角坐标，找不到返回 [-1, -1]
        def check(i: int, j: int) -> bool:  # 内部函数 check：检查以 (i, j) 为左上角的子矩阵是否与 pattern 匹配
            d1 = {}  # d1：字母 -> board 数字的映射
            d2 = {}  # d2：board 数字 -> 字母 的反向映射，保证不同字母不会对应同一个数字
            for a in range(r):  # 遍历模式内的行偏移
                for b in range(c):  # 遍历模式内的列偏移
                    x, y = i + a, j + b  # 换算出对应的 board 坐标
                    if pattern[a][b].isdigit():  # 模式该位是数字时，要求 board 完全相同
                        if int(pattern[a][b]) != board[x][y]:  # 数字不一致，这个位置不匹配
                            return False  # 匹配失败，提前返回
                    else:  # 模式该位是字母，需要建立并校验双向的一一映射
                        if pattern[a][b] in d1 and d1[pattern[a][b]] != board[x][y]:  # 同一个字母此前已映射到别的数字，违反一致性
                            return False  # 冲突，匹配失败
                        if board[x][y] in d2 and d2[board[x][y]] != pattern[a][b]:  # 该数字此前已被别的字母占用，违反一一对应
                            return False  # 冲突，匹配失败
                        d1[pattern[a][b]] = board[x][y]  # 记录正向映射：字母 -> 数字
                        d2[board[x][y]] = pattern[a][b]  # 记录反向映射：数字 -> 字母
            return True  # 所有格子都通过校验，说明匹配成功

        m, n = len(board), len(board[0])  # board 的行数与列数
        r, c = len(pattern), len(pattern[0])  # pattern 的行数与列数，也就是要匹配的子矩阵大小
        for i in range(m - r + 1):  # 枚举子矩阵左上角的行，最多到 m - r 才能放得下模式
            for j in range(n - c + 1):  # 枚举子矩阵左上角的列，最多到 n - c
                if check(i, j):  # 该位置能匹配
                    return [i, j]  # 返回找到的左上角坐标
        return [-1, -1]  # 没有任何位置匹配，按题目要求返回 [-1, -1]
