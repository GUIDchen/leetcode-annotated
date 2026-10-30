# 题目：921. 使括号有效的最少添加（Minimum Add to Make Parentheses Valid）
# 思路：用栈抵消配对的括号，最后栈里剩下的未匹配括号个数就是最少需要添加的个数。
# 时间复杂度：O(n)，每个字符进出栈至多一次；空间复杂度：O(n)，栈最多存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def minAddToMakeValid(self, s: str) -> int:  # s 是只含 '(' 与 ')' 的字符串
        stk = []  # 用列表当栈，只保存尚未匹配的括号
        for c in s:  # 逐个扫描字符
            if c == ')' and stk and stk[-1] == '(':  # 右括号且栈顶是左括号，说明这一对可以匹配
                stk.pop()  # 弹出已匹配的左括号
            else:  # 其他情况：左括号，或暂时无法匹配的右括号
                stk.append(c)  # 压栈，留给后续字符匹配
        return len(stk)  # 栈里剩下的每个括号都要各补一个配对，个数即答案
