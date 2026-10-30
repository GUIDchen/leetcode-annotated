# 3823. Reverse Letters Then Special Characters in a String | 3823. 反转一个字符串里的字母后反转特殊字符
# 核心思路：先把字母与非字母分别入栈，再按原串的顺序从对应栈顶弹出，天然实现两类字符各自逆序
# 复杂度：时间 O(n)，空间 O(n)
class Solution:
    def reverseByType(self, s: str) -> str:  # 把字母与非字母分别逆序，位置上的类别保持不变
        a = []  # 字母栈：按原顺序入栈，出栈即逆序
        b = []  # 特殊字符栈：按原顺序入栈，出栈即逆序
        for c in s:  # 第一遍遍历：按字符类别分别入栈
            if c.isalpha():  # 当前字符是字母
                a.append(c)  # 存入字母栈
            else:  # 当前字符不是字母
                b.append(c)  # 存入特殊字符栈
        return ''.join(a.pop() if c.isalpha() else b.pop() for c in s)  # 第二遍遍历：遇到字母弹字母栈顶、否则弹特殊字符栈顶，拼接成新串
