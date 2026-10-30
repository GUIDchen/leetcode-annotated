# 题目：1003. 检查替换后的词是否有效（Check If Word Is Valid After Substitutions）
# 思路：用列表当栈，从左到右逐个入栈；只要栈顶三个字符是 abc，就把它们整体弹出；扫描结束栈空则字符串有效。
# 时间复杂度：O(n)，每个字符入栈出栈各一次；空间复杂度：O(n)，栈最坏保存全部字符。
class Solution:  # LeetCode 约定的题解类
    def isValid(self, s: str) -> bool:  # s：待检验的字符串；返回它能否由 abc 不断插入得到
        if len(s) % 3:  # 每次插入固定增加 3 个字符，长度必须是 3 的倍数
            return False  # 长度不合法，直接返回 False
        t = []  # 用列表当栈，保存还没被消掉的前缀
        for c in s:  # 从左到右扫描每个字符
            t.append(c)  # 当前字符入栈
            if ''.join(t[-3:]) == 'abc':  # 取栈顶三个字符拼起来，若正好是 abc 说明来自同一次插入
                t[-3:] = []  # 把这三个字符整体弹出，等价于撤销一次插入
        return not t  # 栈空说明能全部消掉，字符串有效
