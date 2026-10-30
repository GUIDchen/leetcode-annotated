# 题目：772. 基本计算器 III（Basic Calculator III）
# 核心思路：把字符串放进双端队列做全局游标，递归下降处理括号；每层用栈暂存加减结果，遇到乘除立刻与栈顶结合。
# 时间复杂度 O(n)（每个字符进出队列各一次）；空间复杂度 O(n)（字符队列 + 递归栈 + 运算栈）。
class Solution:  # LeetCode 约定的题解类
    def calculate(self, s: str) -> int:  # s：含 + - * / 与括号的表达式字符串，返回其整数值
        def dfs(q):  # 内层递归函数，q 是各层共享的字符双端队列
            num, sign, stk = 0, "+", []  # num 累积当前操作数，sign 是上一个运算符，stk 暂存加数
            while q:  # 队列不空就继续处理当前层
                c = q.popleft()  # 从队首弹出一个字符，保证每个字符只处理一次
                if c.isdigit():  # 是数字字符，继续拼接多位数字
                    num = num * 10 + int(c)  # 十进制累积：旧值乘 10 再加上新数位
                if c == "(":  # 遇到左括号，开始子表达式
                    num = dfs(q)  # 递归求括号内的值，结果作为当前操作数
                if c in "+-*/)" or not q:  # 遇到运算符、右括号，或队列空（表达式结尾也必须结算）
                    match sign:  # 按上一个运算符决定如何结算 num
                        case "+":  # 分支：上一个运算符是加号
                            stk.append(num)  # 正数原样入栈
                        case "-":  # 分支：上一个运算符是减号
                            stk.append(-num)  # 取反入栈，把减法统一成加法
                        case "*":  # 分支：上一个运算符是乘号
                            stk.append(stk.pop() * num)  # 立刻与栈顶相乘，实现乘除优先于加减
                        case "/":  # 分支：上一个运算符是除号
                            stk.append(int(stk.pop() / num))  # 用 int() 做向零截断的整除，与题目要求的除法一致
                    num, sign = 0, c  # 结算完毕，操作数清零并记住当前运算符
                if c == ")":  # 遇到右括号，本层子表达式结束
                    break  # 跳出循环，把控制权交回上一层
            return sum(stk)  # 栈中全是同号的加数，求和即为本层结果

        return dfs(deque(s))  # 把字符串装进 deque 后启动递归