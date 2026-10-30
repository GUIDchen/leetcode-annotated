# 题目：79. 单词搜索（Word Search）
# 思路：网格 DFS 回溯。从每个格子出发尝试匹配 word，匹配到某一位后用临时标记 "0" 封住已用格子防止重复经过，四个方向递归，失败则恢复原字符。
# 时间复杂度：O(m * n * 3^L)，L 为单词长度，每个起点最多向三个方向继续；空间复杂度：O(L)，递归栈深度为单词长度。
class Solution:  # LeetCode 约定的题解类
    def exist(self, board: List[List[str]], word: str) -> bool:  # board 是字符网格，word 是待匹配的单词
        def dfs(i: int, j: int, k: int) -> bool:  # 从 (i, j) 出发匹配 word[k...]，返回是否匹配成功
            if k == len(word) - 1:  # 已经匹配到单词的最后一个字符，无需再向四周扩展
                return board[i][j] == word[k]  # 当前格子是否正好等于最后一个字符
            if board[i][j] != word[k]:  # 当前格子的字符和要匹配的字符不同
                return False  # 这个方向走不通，立即回溯
            c = board[i][j]  # 先暂存当前格子的原字符，回溯时要还原
            board[i][j] = "0"  # 用 "0" 标记为「已使用」，防止同一条路径重复经过同一个格子
            for a, b in pairwise((-1, 0, 1, 0, -1)):  # 用 pairwise 把偏移量两两配对，得到上、右、下、左四个方向
                x, y = i + a, j + b  # 由方向偏移算出下一个格子的坐标
                ok = 0 <= x < m and 0 <= y < n and board[x][y] != "0"  # 先判断不越界且没被本路径使用过
                if ok and dfs(x, y, k + 1):  # 条件满足且后续字符也能匹配成功
                    return True  # 找到完整路径，直接返回成功
            board[i][j] = c  # 四个方向都失败，恢复原字符，让其他搜索路径还能使用这个格子
            return False  # 以 (i, j) 为起点匹配 word[k...] 失败

        m, n = len(board), len(board[0])  # m 是行数，n 是列数，供内部 dfs 做边界判断
        return any(dfs(i, j, 0) for i in range(m) for j in range(n))  # 枚举所有起点，任意一个匹配成功即返回 True
