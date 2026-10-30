# 题目：224. 基本计算器（Basic Calculator）
# 思路：一次扫描，ans 累加当前层的值、sign 记录下一个数的符号；遇左括号把外层 ans 与 sign 压栈并清零，遇右括号弹栈合成 ans = 外层sign * ans + 外层ans。
# 时间复杂度：O(n)，每个字符最多被扫一遍；空间复杂度：O(n)，栈深等于括号嵌套层数。
class Solution:  # LeetCode 约定的题解类
    def calculate(self, s: str) -> int:  # s 是只含数字、空格、+ - ( ) 的合法表达式，返回它的整数值
        stk = []  # 用列表当栈，成对保存外层现场（先 ans 后 sign）
        ans, sign = 0, 1  # ans 当前累加结果；sign 是下一个数字要乘的符号，默认正号
        i, n = 0, len(s)  # i 扫描下标；n 是长度，先缓存避免重复求 len
        while i < n:  # 从左到右扫描整个表达式
            if s[i].isdigit():  # 遇到数字，就一次性读完这一整段多位数
                x = 0  # x 用来累积这个多位数
                j = i  # j 从 i 出发向右寻找连续的数字
                while j < n and s[j].isdigit():  # 数字还没结束就继续读下一位
                    x = x * 10 + int(s[j])  # 十进制左移一位再加上新的一位数字
                    j += 1  # 指针后移，准备读下一个字符
                ans += sign * x  # 把整个数按当前符号并入结果
                i = j - 1  # 循环末尾还会 i += 1，这里退一格让 i 停在数字末位
            elif s[i] == "+":  # 加号：后面的数字取正
                sign = 1  # 正号作用于下一个数字
            elif s[i] == "-":  # 减号：后面的数字取负
                sign = -1  # 负号作用于下一个数字
            elif s[i] == "(":  # 左括号：先把外层现场压栈保存
                stk.append(ans)  # 保存括号外已经算出的累加值
                stk.append(sign)  # 保存整个括号块前面的符号
                ans, sign = 0, 1  # 括号内从头开始独立计算，符号也重新从正号起
            elif s[i] == ")":  # 右括号：括号块算完，弹栈恢复外层现场并合并
                ans = stk.pop() * ans + stk.pop()  # 先弹出的是外层符号，用它缩放括号内的值，再弹出外层累加值相加
            i += 1  # 无论哪个分支，处理完当前字符都要后移一位
        return ans  # 扫描结束时 ans 就是整个表达式的值
