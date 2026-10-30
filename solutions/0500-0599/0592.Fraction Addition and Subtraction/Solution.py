# 题目：592. 分数加减运算（Fraction Addition and Subtraction）
# 思路：先给表达式补上前导符号，再逐项解析出「符号 + 分子/分母」，统一通分到公分母 6*7*8*9*10 = 2520 上累加分子，最后用 gcd 约分。
# 时间复杂度：O(n)，只需线性扫描一遍表达式；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def fractionAddition(self, expression: str) -> str:  # expression 是形如 "-1/2+1/3" 的分数加减表达式
        x, y = 0, 6 * 7 * 8 * 9 * 10  # x 是累加后的分子，y 是公分母 2520（1~10 的最小公倍数）
        if expression[0].isdigit():  # 表达式可能不带前导符号
            expression = '+' + expression  # 补一个 '+'，让后面统一按「符号开头」的格式解析
        i, n = 0, len(expression)  # i 是当前解析位置，n 是表达式长度
        while i < n:  # 逐项解析表达式
            sign = -1 if expression[i] == '-' else 1  # 当前这一项的符号
            i += 1  # 跳过符号，i 指向分子数字的开头
            j = i  # 从 i 开始找这一项的结尾
            while j < n and expression[j] not in '+-':  # 遇到下一个 '+'、'-' 或字符串末尾就停下
                j += 1  # 继续右移找边界
            s = expression[i:j]  # 取出形如 "a/b" 的分数
            a, b = s.split('/')  # 按 '/' 拆成分子 a 与分母 b（此时还是字符串）
            x += sign * int(a) * y // int(b)  # 通分：分子乘以 公分母/分母 之后按符号累加（y 能被 b 整除，所以结果是整数）
            i = j  # 从下一个符号处继续解析
        z = gcd(x, y)  # 求分子分母的最大公约数用于约分（x 为 0 时 gcd 返回 y）
        x //= z  # 分子约分
        y //= z  # 分母约分
        return f'{x}/{y}'  # 按题目要求的 "分子/分母" 格式输出
