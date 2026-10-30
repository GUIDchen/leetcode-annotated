# 题目：3749. 计算有效表达式（Evaluate Valid Expressions）
# 核心思路：表达式是嵌套的 op(a,b) 结构，用递归下降解析：遇到数字或负号就解析字面量，否则先读到左括号取出运算符，再依次解析两个子表达式并按 add/sub/mul/div 求值，返回 (结果, 下一个未处理下标)。
# 复杂度：时间 O(n)，每个字符只会被扫描常数次；空间 O(n)，递归栈深度与表达式嵌套层数成正比。
class Solution:  # LeetCode 约定的题解类
    def evaluateExpression(self, expression: str) -> int:  # 解析并计算嵌套表达式 expression，返回其整数值
        def parse(i: int) -> (int, int):  # 递归下降：parse(i) 解析从 i 开始的子表达式，返回 (结果, 下一个未处理下标)
            if expression[i].isdigit() or expression[i] == "-":  # 以数字或负号开头，说明当前是一个整数字面量
                j = i  # j 用于向后扫描字面量的结束位置
                if expression[j] == "-":  # 首位是负号时先跳过它
                    j += 1  # 跳过负号
                while j < len(expression) and expression[j].isdigit():  # 继续吞掉后面连续的数字字符
                    j += 1  # 指针后移
                return int(expression[i:j]), j  # 把 [i, j) 这段子串转成整数并返回，同时给出结束下标

            j = i  # 否则这里是 op(a,b) 形式，先扫描到左括号确定运算符
            while expression[j] != "(":  # 一直右移直到遇到左括号 '('
                j += 1  # 指针后移
            op = expression[i:j]  # 取出运算符字符串 op（add/sub/mul/div）
            j += 1  # 跳过左括号 '('
            val1, j = parse(j)  # 递归解析第一个参数 a，j 更新为它之后的下标

            j += 1  # 跳过参数之间的逗号 ','
            val2, j = parse(j)  # 递归解析第二个参数 b，j 更新为它之后的下标
            j += 1  # 跳过右括号 ')'
            res = 0  # res 存放本次运算的结果
            match op:  # 按运算符分派到对应的运算
                case "add":  # 加法
                    res = val1 + val2  # a + b
                case "sub":  # 减法
                    res = val1 - val2  # a - b
                case "mul":  # 乘法
                    res = val1 * val2  # a * b
                case "div":  # 除法，题目保证整除，用 // 保持整数结果
                    res = val1 // val2  # a // b
            return res, j  # 返回结果和下一个未处理的下标

        return parse(0)[0]  # 从下标 0 开始解析整个表达式，取结果部分
