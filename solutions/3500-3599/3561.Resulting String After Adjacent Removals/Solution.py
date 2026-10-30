# 3561. 移除相邻字符 / Resulting String After Adjacent Removals
# 核心思路：用栈模拟删除过程，若栈顶字符与当前字符的字母序号差为 1 或 25（即相邻或首尾相邻）则弹出栈顶，否则把当前字符入栈。
# 复杂度：时间 O(n)，空间 O(n)
class Solution:  # 定义解题类
    def resultingString(self, s: str) -> str:  # 返回反复删除相邻的“循环相邻”字符后剩下的字符串
        stk = []  # 用栈保存尚未被删除的字符
        for c in s:  # 从左到右扫描字符串
            if stk and abs(ord(c) - ord(stk[-1])) in (1, 25):  # 栈顶与当前字符相邻或跨越 z/a 相邻时可以删除
                stk.pop()  # 弹出栈顶，相当于把这一对字符删掉
            else:  # 不能删除时
                stk.append(c)  # 当前字符入栈
        return "".join(stk)  # 栈中剩下的字符拼成结果字符串
