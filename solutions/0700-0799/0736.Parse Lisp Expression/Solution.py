# 题目：736. Lisp 语法解析（Parse Lisp Expression）
# 思路：用下标 i 在字符串上做递归下降解析；scope 记录「变量名 → 各层 let 的值栈」，遇到括号按 let/add/mult 分派，遇到变量或整数就地求值。
# 时间复杂度：O(n)，每个字符只被常数次扫描；空间复杂度：O(n)，作用域栈与递归深度均为 O(n)。
class Solution:  # LeetCode 约定的题解类
    def evaluate(self, expression: str) -> int:  # expression：待求值的 Lisp 表达式
        def parseVar():  # 内嵌函数：从 i 开始读出一个变量名
            nonlocal i  # 声明要修改外层函数（evaluate）里定义的 i
            j = i  # 记下变量名的起点
            while i < n and expression[i] not in " )":  # 名字一直延续到空格、右括号或字符串末尾为止
                i += 1  # 指针前进到下一位
            return expression[j:i]  # 返回 [j, i) 这一段，即变量名本身

        def parseInt():  # 内嵌函数：从 i 开始读出一个整数（可能带负号）
            nonlocal i  # 同样需要修改外层的指针 i
            sign, v = 1, 0  # sign 为符号位，v 为累加的绝对值
            if expression[i] == "-":  # 遇到负号说明这是负数
                sign = -1  # 记下负号
                i += 1  # 跳过负号
            while i < n and expression[i].isdigit():  # 逐位读取数字字符
                v = v * 10 + int(expression[i])  # 把新的一位接到当前数值后面
                i += 1  # 移动到下一位
            return sign * v  # 补上符号位后返回结果

        def eval():  # 内嵌函数：递归求值当前表达式（整数、变量或括号表达式）
            nonlocal i  # 需要修改外层的指针 i
            if expression[i] != "(":  # 不以 ( 开头：是变量名就取作用域栈顶值，是数字就直接解析
                return scope[parseVar()][-1] if expression[i].islower() else parseInt()  # 变量名返回 scope 中该变量最后一层的值，否则按整数解析
            i += 1  # 跨过左括号 (，i 指向操作符首字母
            if expression[i] == "l":  # 首字母是 l ⇒ 说明是 let 表达式
                i += 4  # 跳过 "let " 这 4 个字符，指向第一个绑定名或结尾表达式
                vars = []  # 记录本次 let 真正压栈的变量名，退出时逐个弹出以恢复作用域
                while 1:  # 循环处理 let 的绑定列表与结尾表达式
                    var = parseVar()  # 读出当前这一段变量名
                    if expression[i] == ")":  # 变量名后紧跟 ) ⇒ 它是 let 的结尾表达式，直接取它的值
                        ans = scope[var][-1]  # 取出该变量当前的值作为整个 let 的结果
                        break  # 拿到结果后跳出循环
                    vars.append(var)  # 否则 var 是一个绑定名，先记录下来
                    i += 1  # 跳过绑定名与值之间的空格
                    scope[var].append(eval())  # 递归求值绑定的右侧并压入作用域栈
                    i += 1  # 跳过值与下一个 token 之间的空格
                    if not expression[i].islower():  # 下一个 token 不是小写字母 ⇒ 是 (add/mult …)，即结尾表达式
                        ans = eval()  # 求值结尾表达式作为整个 let 的结果
                        break  # 拿到结果后跳出循环
                for v in vars:  # 撤销本次 let 引入的绑定，让同名变量的外层值重新可见
                    scope[v].pop()  # 每个绑定弹出一层
            else:  # 否则是 add 或 mult 表达式
                add = expression[i] == "a"  # 首字母是 a ⇒ add，否则是 mult
                i += 4 if add else 5  # 跳过 "add "（4 个字符）或 "mult "（5 个字符）
                a = eval()  # 递归求第一个操作数
                i += 1  # 跳过两个操作数之间的空格
                b = eval()  # 递归求第二个操作数
                ans = a + b if add else a * b  # 按运算符合并两个操作数的结果
            i += 1  # 跨过对应的右括号 )
            return ans  # 返回本层的求值结果

        i, n = 0, len(expression)  # 初始化解析指针 i 与字符串长度 n
        scope = defaultdict(list)  # 作用域：变量名 → 值列表，let 可嵌套所以用列表当栈
        return eval()  # 从下标 0 开始对整个表达式求值
