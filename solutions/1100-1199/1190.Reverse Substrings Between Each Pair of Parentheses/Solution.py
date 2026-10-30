# 题目：1190. 反转每对括号间的子串（Reverse Substrings Between Each Pair of Parentheses）
# 思路：用列表当栈，遇 ')' 就不断弹出栈顶直到 '('，弹出的顺序恰好是逆序，再把这些字符接回栈顶。
# 时间复杂度：O(n^2)，字符串拼接与弹出是主要开销；空间复杂度：O(n)，栈最多存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def reverseParentheses(self, s: str) -> str:  # 返回括号反转后的字符串
        stk = []  # 用列表当栈
        for c in s:  # 逐字符处理
            if c == ")":  # 遇到右括号：反转本层括号内的内容
                t = []  # 暂存弹出的字符，顺序天然是逆序
                while stk[-1] != "(":  # 一直弹到左括号为止
                    t.append(stk.pop())  # 逆序弹出即完成反转
                stk.pop()  # 丢掉配对的左括号
                stk.extend(t)  # 把反转后的内容接回栈顶
            else:  # 左括号或普通字符
                stk.append(c)  # 直接入栈
        return "".join(stk)  # 拼接成结果字符串返回
