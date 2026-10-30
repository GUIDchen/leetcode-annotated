# 题目：2075. 解码斜向换位密码（Decode the Slanted Ciphertext）
# 思路：把密文按 rows 行等宽排成矩阵，从每一列的顶部出发沿右下方向斜走收集字符，拼接后再去掉尾部补位空格。
# 时间复杂度：O(len(encodedText))，每个字符访问一次；空间复杂度：O(len(encodedText))，用于存放答案。
class Solution:  # LeetCode 约定的题解类
    def decodeCiphertext(self, encodedText: str, rows: int) -> str:  # encodedText 是密文，rows 是原始矩阵的行数
        ans = []  # 用列表按斜线顺序收集解码出的字符
        cols = len(encodedText) // rows  # 每行有 cols 个字符，密文长度 = rows * cols
        for j in range(cols):  # 枚举每条斜线的起点列 j
            x, y = 0, j  # 斜线从第 0 行、第 j 列出发
            while x < rows and y < cols:  # 行、列都不越界就继续斜走
                ans.append(encodedText[x * cols + y])  # 一维下标 = 行号 * 列宽 + 列号
                x, y = x + 1, y + 1  # 同时向右下移动一步
        return ''.join(ans).rstrip()  # 拼接后去掉尾部补的空格，得到原文
