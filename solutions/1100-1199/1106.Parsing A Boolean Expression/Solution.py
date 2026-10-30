# 题目：1106. 解析布尔表达式（Parsing A Boolean Expression）
# 思路：用列表模拟栈，遇到 ')' 就连续弹出 't'/'f' 统计真假个数，再弹出操作符用 match 求值并压回栈中。
# 时间复杂度：O(n)，每个字符至多入栈出栈各一次；空间复杂度：O(n)，栈最深可达表达式长度。
class Solution:  # LeetCode 约定的题解类
    def parseBoolExpr(self, expression: str) -> bool:  # expression 是题目保证合法的布尔表达式字符串
        stk = []  # 用列表当栈：混存操作符 '!' '&' '|' 与操作数 't' 'f'
        for c in expression:  # 从左到右逐个字符扫描
            if c in 'tf!&|':  # 操作符和操作数才需要入栈
                stk.append(c)  # 压栈；括号与逗号只是分隔符，直接忽略
            elif c == ')':  # 右括号表示一个子表达式结束，可以就地求值
                t = f = 0  # 统计子表达式内真值与假值的个数
                while stk[-1] in 'tf':  # 从栈顶连续弹出布尔操作数
                    t += stk[-1] == 't'  # 栈顶是真值则 t 加一（bool 参与加法会转成 0/1）
                    f += stk[-1] == 'f'  # 栈顶是假值则 f 加一
                    stk.pop()  # 弹出已统计过的操作数
                match stk.pop():  # 操作数清空后栈顶即操作符，弹出并按值分派（Python 3.10 结构化模式匹配）
                    case '!':
                        c = 't' if f else 'f'  # 取反：存在假值则结果为真
                    case '&':
                        c = 'f' if f else 't'  # 与：存在假值则结果为假
                    case '|':
                        c = 't' if t else 'f'  # 或：存在真值则结果为真
                stk.append(c)  # 把子表达式的求值结果压回栈顶，供外层继续使用
        return stk[0] == 't'  # 全部求值完，栈中只剩一个结果字符
