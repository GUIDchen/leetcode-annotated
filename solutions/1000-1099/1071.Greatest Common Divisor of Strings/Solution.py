# 题目：1071. 字符串的最大公因子（Greatest Common Divisor of Strings）
# 思路：公因子长度必不超过较短串，从长到短枚举前缀，用「重复拼接能否恰好等于原串」判定是否整除，第一个命中即最长。
# 时间复杂度：O(L³)，枚举 O(L) 个长度、每次校验拼接 O(L) 且字符串拼接 O(L)；空间复杂度：O(L)，拼接用的临时串。
class Solution:  # LeetCode 约定的题解类
    def gcdOfStrings(self, str1: str, str2: str) -> str:  # str1、str2：两个输入串；返回能同时整除它们的最长字符串
        def check(a, b):  # 判断串 a 是否是 b 的整因子（a 重复若干次后恰好等于 b）
            c = ""  # 累积拼接结果，从空串开始
            while len(c) < len(b):  # 一直拼到长度不小于 b 为止
                c += a  # 每次追加一份 a
            return c == b  # 结束时长度恰好相等且内容相同，才说明 a 能整除 b

        for i in range(min(len(str1), len(str2)), 0, -1):  # 公因子长度不超过较短串，从长到短枚举，第一个满足的就是最大公因子
            t = str1[:i]  # 候选因子：str1 的前 i 个字符
            if check(t, str1) and check(t, str2):  # 必须同时整除两个串
                return t  # 从长到短第一个满足条件的前缀即答案
        return ''  # 所有长度都不行，说明不存在公共整因子，返回空串
