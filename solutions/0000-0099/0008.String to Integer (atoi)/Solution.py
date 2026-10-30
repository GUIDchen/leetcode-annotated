# 题目：8. 字符串转换整数 (atoi)（String to Integer (atoi)）
# 思路：跳过前导空格与一个正负号，逐位累加数字；每步用 2147483647 // 10 和末位阈值预判溢出，越界即返回 32 位边界。
# 时间复杂度：O(n)，只扫描一遍字符串；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def myAtoi(self, s: str) -> int:  # 按 atoi 规则把字符串转成 32 位整数
        if not s:  # 空字符串没有可解析内容
            return 0  # 直接返回 0
        n = len(s)  # 字符串长度
        if n == 0:  # 与上一行重复的兜底检查（保留原题解逻辑）
            return 0  # 直接返回 0
        i = 0  # 扫描下标
        while s[i] == ' ':  # 跳过前导空格
            i += 1  # 右移一位
            # 仅包含空格
            if i == n:  # 已经走到字符串末尾，说明全是空格
                return 0  # 没有任何数字，返回 0
        sign = -1 if s[i] == '-' else 1  # 根据被跳过的首字符确定符号
        if s[i] in ['-', '+']:  # 存在正负号时跨过它
            i += 1  # 指向第一个数字
        res, flag = 0, (2**31 - 1) // 10  # res 为累加结果，flag 是 INT_MAX // 10 的溢出阈值
        while i < n:  # 遍历剩余字符
            # 非数字，跳出循环体
            if not s[i].isdigit():  # 遇到非数字字符立即停止解析
                break  # 跳出解析循环
            c = int(s[i])  # 取当前位的数值
            # 溢出判断
            if res > flag or (res == flag and c > 7):  # 超过 2147483647 的边界：末位最多到 7
                return 2**31 - 1 if sign > 0 else -(2**31)  # 按符号返回 32 位上下界
            res = res * 10 + c  # 累加这一位
            i += 1  # 前进到下一位
        return sign * res  # 乘符号得到最终答案
