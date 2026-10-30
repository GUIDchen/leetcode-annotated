# 题目：6. Z 字形变换（Zigzag Conversion）
# 思路：每行准备一个列表，用方向变量 k 让行号在 0 与 numRows-1 之间折返，字符按遍历顺序追加到对应行，最后按行拼接。
# 时间复杂度：O(n)，每个字符只写入、读出各一次；空间复杂度：O(n)，各行列表合计存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def convert(self, s: str, numRows: int) -> str:  # s 为输入字符串，numRows 为 Z 字形行数
        if numRows == 1:  # 只有一行时不需要变换
            return s  # 原样返回
        g = [[] for _ in range(numRows)]  # 每行一个列表；列表推导保证各行是独立对象，不会共享同一块内存
        i, k = 0, -1  # i 为当前行号，k 为行号移动方向（+1 下行、-1 上行）
        for c in s:  # 按原顺序遍历字符
            g[i].append(c)  # 字符追加到当前行
            if i == 0 or i == numRows - 1:  # 走到首行或末行时需要折返
                k = -k  # 反转移动方向
            i += k  # 行号沿方向移动一格
        return ''.join(chain(*g))  # 用 chain 展开各行列表，再 join 成一个字符串
