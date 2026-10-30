# 题目：150. 逆波兰表达式求值（Evaluate Reverse Polish Notation）
# 思路：后缀表达式用栈求值——遇到操作数就入栈，遇到运算符就弹出左右操作数算完再压回。
# 时间复杂度：O(n)，每个 token 只处理一次；空间复杂度：O(n)，栈最多存 n/2 个操作数。
import operator  # 用 operator 把运算符映射成函数，避免写一长串 if


class Solution:  # 题目要求的题解类
    def evalRPN(self, tokens: List[str]) -> int:  # tokens 是后缀表达式，返回求值结果
        opt = {  # 运算符 → 对应二元函数的映射表
            "+": operator.add,  # 加法
            "-": operator.sub,  # 减法
            "*": operator.mul,  # 乘法
            "/": operator.truediv,  # 浮点除法，后面用 int() 截断成题目要求的向零取整
        }  # 映射表定义结束
        s = []  # 运算数栈
        for token in tokens:  # 从左到右扫描每个 token
            if token in opt:  # token 是运算符
                s.append(int(opt[token](s.pop(-2), s.pop(-1))))  # 先弹左操作数（pop(-2)）再弹右操作数（pop(-1)），算完取整压回栈
            else:  # 否则这个 token 是操作数
                s.append(int(token))  # 字符串转整数后入栈
        return s[0]  # 扫描结束，栈里只剩一个元素，就是表达式的值
