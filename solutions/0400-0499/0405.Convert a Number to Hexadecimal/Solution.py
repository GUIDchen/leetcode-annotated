# 题目：405. 数字转换为十六进制数（Convert a Number to Hexadecimal）
# 思路：按补码逐组取位。Python 的负数右移也是算术移位，配合 0xF 掩码就能逐位取出 32 位补码的 8 个十六进制位，再跳过前导 0。
# 时间复杂度：O(1)，固定循环 8 次；空间复杂度：O(1)，结果最长 8 个字符。
class Solution:  # LeetCode 约定的题解类
    def toHex(self, num: int) -> str:  # 把整数转成十六进制字符串，负数按补码解释、不带负号
        if num == 0:  # 0 单独处理
            return '0'  # 返回 "0"
        chars = '0123456789abcdef'  # 十六进制字符表，下标就是数值
        s = []  # 用列表收集每一位字符，最后拼接
        for i in range(7, -1, -1):  # 从最高的第 7 组到最低的第 0 组，共 8 组
            x = (num >> (4 * i)) & 0xF  # 右移取当前组，再用 0xF 只保留低 4 位（负数按补码得到正确的位）
            if s or x != 0:  # 前面已有非零位，或这一组本身非零时才记录，跳过前导 0
                s.append(chars[x])  # 把对应字符追加进列表
        return ''.join(s)  # 拼接成字符串返回
