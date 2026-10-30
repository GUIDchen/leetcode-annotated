# 题目：537. 复数乘法（Complex Number Multiplication）
# 思路：把两个字符串各解析成实部 a 与虚部 b，再按 (a1+b1i)(a2+b2i) = (a1a2-b1b2) + (a1b2+a2b1)i 直接算出结果。
# 时间复杂度：O(len1+len2)，只做两次线性解析；空间复杂度：O(len1+len2)，用于存放输出字符串。
class Solution:  # LeetCode 约定的题解类
    def complexNumberMultiply(self, num1: str, num2: str) -> str:  # 输入两个 "a+bi" 形式的字符串，返回它们乘积的同种形式
        a1, b1 = map(int, num1[:-1].split("+"))  # num1[:-1] 去掉末尾的 'i'，再按 '+' 切分转成整数，得到实部 a1 与虚部 b1
        a2, b2 = map(int, num2[:-1].split("+"))  # 同样得到第二个复数的实部 a2 与虚部 b2
        return f"{a1 * a2 - b1 * b2}+{a1 * b2 + a2 * b1}i"  # 用 f-string 按复数乘法公式拼出 "实部+虚部i" 形式的结果
