# 题目：1812. 判断国际象棋棋盘中一个格子的颜色（Determine Color of a Chessboard Square）
# 思路：棋盘上同色格子的「列字母 + 行数字」奇偶性相同，直接看两字符编码之和模 2 是否等于 1 即可。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def squareIsWhite(self, coordinates: str) -> bool:  # coordinates：形如 e4 的两字符坐标，下标 0 是列字母、下标 1 是行数字
        return (ord(coordinates[0]) + ord(coordinates[1])) % 2 == 1  # ord 取出字符编码，两码之和为奇数就是白格
