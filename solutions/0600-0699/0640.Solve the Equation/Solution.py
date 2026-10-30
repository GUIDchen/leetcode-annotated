# 题目：640. 求解方程（Solve the Equation）
# 核心思路：分别解析等式左右两边，各自累加成「x 系数 + 常数项」，得到 x1·x + y1 = x2·x + y2 后按系数差是否为 0 分三种情况回答。
# 时间复杂度：O(n)，每个字符只扫一次；空间复杂度：O(1)，只用常数个整型变量。
class Solution:  # LeetCode 约定的题解类
    def solveEquation(self, equation: str) -> str:  # equation：形如 x+5-3+x=6+x-2 的方程，返回解的描述字符串
        def f(s):  # 内部函数：把表达式 s 解析成 (x 的系数, 常数项)
            x = y = 0  # x：累计的 x 系数；y：累计的常数项
            if s[0] != '-':  # 表达式不是以负号开头时
                s = '+' + s  # 补一个 + 号，让后面统一按「符号 + 项」的格式解析
            i, n = 0, len(s)  # i：扫描下标；n：表达式长度
            while i < n:  # 逐个「符号 + 项」地扫描
                sign = 1 if s[i] == '+' else -1  # 取当前项的符号
                i += 1  # 跳过符号字符
                j = i  # j 用来找这一项的结尾
                while j < n and s[j] not in '+-':  # 一直走到下一个符号或字符串末尾
                    j += 1  # 项内部继续前进
                v = s[i:j]  # 截出这一项的文本，例如 12x、5、x
                if v[-1] == 'x':  # 这一项含有 x
                    x += sign * (int(v[:-1]) if len(v) > 1 else 1)  # 系数是省略的 1，还是显式写出的数字
                else:  # 否则是纯常数项
                    y += sign * int(v)  # 带符号把常数累加进去
                i = j  # 从下一个符号处继续扫描
            return x, y  # 返回该边的 (x 系数, 常数项)

        a, b = equation.split('=')  # 以等号把方程拆成左右两边
        x1, y1 = f(a)  # 左边的 x 系数与常数项
        x2, y2 = f(b)  # 右边的 x 系数与常数项
        if x1 == x2:  # 两边 x 系数相同，就退化成常数比较
            return 'Infinite solutions' if y1 == y2 else 'No solution'  # 常数也相等则无穷多解，否则无解
        return f'x={(y2 - y1) // (x1 - x2)}'  # 唯一解：x = 常数差 / 系数差，用整除得到整数结果
