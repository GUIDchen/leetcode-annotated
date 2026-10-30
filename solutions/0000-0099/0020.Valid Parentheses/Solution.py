# 题目：20. 有效的括号（Valid Parentheses）
# 思路：用栈保存「之后必须出现的右括号」；遇左括号压入配对的右括号，遇右括号则必须与栈顶相同。
# 时间复杂度：O(n)，每个字符最多进出栈各一次；空间复杂度：O(n)，栈最坏存放 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def isValid(self, s: str) -> bool:  # s：只由 ()[]{} 组成的括号串
        stk = []  # 用列表当栈：append 入栈、pop 出栈、末尾元素即栈顶
        d = {'(': ')', '[': ']', '{': '}'}  # 映射表：左括号 → 与之配对的右括号
        for c in s:  # 从左到右依次扫描每个字符
            if c in d:  # c 是左括号（在字典的键里）
                stk.append(d[c])  # 把「接下来必须出现的右括号」压入栈，等待后续匹配
            elif not stk or stk.pop() != c:  # 遇右括号：栈空（无左括号可配）或弹出来的不是它，即不合法
                return False  # 括号序列不合法
        return not stk  # 全部匹配完栈应为空；非空说明还有左括号没闭合
