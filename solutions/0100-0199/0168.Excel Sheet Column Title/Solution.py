# 题目：168. Excel 表列名称（Excel Sheet Column Title）
# 核心思路：本质是 1~26 的「26 进制」转换，每次先减 1 把 A~Z 映射到 0~25，再取模得到当前最低位字母，最后翻转结果。
# 时间复杂度：O(log₂₆ n)，位数即循环次数；空间复杂度：O(log₂₆ n)，存放每一位字母。
class Solution:  # LeetCode 约定的题解类
    def convertToTitle(self, columnNumber: int) -> str:  # 把正整数列号转成对应的 Excel 列名
        res = []  # 从最低位开始收集字母，最后统一反转
        while columnNumber:  # 列号还没归零就继续拆位
            columnNumber -= 1  # 先减 1：把原本 1~26 的取值范围平移成 0~25，才能用取模对应字母
            res.append(chr(ord('A') + columnNumber % 26))  # chr/ord 组合取当前最低位对应的字母
            columnNumber //= 26  # 整除 26，把最低位去掉，继续处理更高位
        return ''.join(res[::-1])  # 收集顺序是低位在前，倒序拼接才是正确的列名
