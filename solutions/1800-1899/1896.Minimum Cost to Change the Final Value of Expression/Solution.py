# 题目：1896. 反转表达式值的最少操作次数（Minimum Cost to Change the Final Value of Expression）
# 思路：双栈（操作数栈 + 运算符栈）按优先级结算中缀表达式，每个子表达式返回 (当前值, 反转它所需的最少操作数)，合并时按 &、| 的真值表分类取最小代价。
# 时间复杂度：O(n)，每个字符进出栈各一次；空间复杂度：O(n)，两个栈的规模与表达式长度同阶。
class Solution:  # LeetCode 约定的题解类
    def minOperationsToFlip(self, expression: str) -> int:  # expression：由 0、1、&、| 与括号构成的布尔表达式
        def merge(a, b, op):  # 合并两个操作数：a、b 都是 (值, 反转代价)，op 是运算符
            v1, c1 = a  # 左操作数的值与反转代价
            v2, c2 = b  # 右操作数的值与反转代价
            if op == '&':  # 先处理与运算
                val = v1 & v2  # 与运算的真值
                if v1 == 1 and v2 == 1:  # 1 & 1 = 1，想把结果反成 0
                    cost = min(c1, c2)  # 反掉任意一个 1 即可
                elif v1 == 0 and v2 == 0:  # 0 & 0 = 0，想把结果反成 1
                    cost = min(c1 + c2, 1 + min(c1, c2))  # 把两个 0 都反成 1，或把 & 改成 | 再反一个（代价 1）
                else:  # 一 0 一 1，结果是 0
                    cost = min(c1 if v1 == 0 else c2, 1)  # 反掉那个 0，或直接把 & 改成 |（代价 1）
            else:  # 否则是或运算
                val = v1 | v2  # 或运算的真值
                if v1 == 0 and v2 == 0:  # 0 | 0 = 0，想把结果反成 1
                    cost = min(c1, c2)  # 反掉任意一个 0 即可
                elif v1 == 1 and v2 == 1:  # 1 | 1 = 1，想把结果反成 0
                    cost = min(c1 + c2, 1 + min(c1, c2))  # 把两个 1 都反掉，或把 | 改成 & 再反一个（代价 1）
                else:  # 一 0 一 1，结果是 1
                    cost = min(c1 if v1 == 1 else c2, 1)  # 反掉那个 1，或直接把 | 改成 &（代价 1）
            return val, cost  # 返回合并后的值与反转代价

        nums = []  # 操作数栈：元素是 (子表达式的值, 反转它所需的最小操作数)
        ops = []  # 运算符栈：存放 &、| 和左括号

        def apply():  # 结算栈顶运算符：弹出两个操作数与运算符，合并后压回
            b = nums.pop()  # 右操作数
            a = nums.pop()  # 左操作数
            nums.append(merge(a, b, ops.pop()))  # 先弹出运算符，合并结果压回操作数栈

        for c in expression:  # 从左到右扫描表达式，做中缀转后缀
            if c == '(':  # 左括号直接入栈
                ops.append(c)  # 记下左括号
            elif c in '01':  # 常量：值即字符本身，反转它需要 1 次操作
                nums.append((int(c), 1))  # 压入 (值, 1)
            elif c in '&|':  # 运算符：先把栈顶同优先级的 & 与 | 全部结算
                while ops and ops[-1] in '&|':  # 栈顶还是运算符就继续结算
                    apply()  # 结算栈顶运算符
                ops.append(c)  # 当前运算符入栈
            else:  # 剩下的是右括号
                while ops[-1] != '(':  # 结算括号内的所有运算
                    apply()  # 结算一个运算符
                ops.pop()  # 弹出左括号
        while ops:  # 扫描结束后结算栈里剩余的运算符
            apply()  # 结算一个运算符
        return nums[-1][1]  # 答案是整个表达式的反转代价
