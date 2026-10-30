# 题目：504. 七进制数（Base 7）
# 思路：不断对 7 取余得到最低位、整除 7 去掉最低位，余数收集到列表里最后反转；0 与负数单独处理。
# 时间复杂度：O(log_7 |num|)；空间复杂度：O(log_7 |num|)，用于存放各位余数。
class Solution:  # LeetCode 约定的题解类
    def convertToBase7(self, num: int) -> str:  # num：待转换的十进制整数；返回其七进制字符串
        if num == 0:  # 0 需要单独返回
            return '0'  # 否则 while 不执行，会返回空字符串
        if num < 0:  # 负数先求正数部分的七进制，再补负号
            return '-' + self.convertToBase7(-num)  # 递归处理相反数，结果前拼接 '-'
        ans = []  # 存放各位余数（低位在前）
        while num:  # 不断取余、整除
            ans.append(str(num % 7))  # 余数是当前最低位，追加到列表末尾
            num //= 7  # 去掉已经处理的最低位
        return ''.join(ans[::-1])  # 列表里低位在前，反转后再拼接成字符串
