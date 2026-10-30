# 题目：1678. 设计 Goal 解析器（Goal Parser Interpretation）
# 思路：链式调用 replace，先把 '()' 换成 'o'，再把 '(al)' 换成 'al'，因为两种模式的长度都是由长到短。
# 时间复杂度：O(n)，两次线性替换；空间复杂度：O(n)，每次 replace 都会生成新字符串。
class Solution:  # LeetCode 约定的题解类
    def interpret(self, command: str) -> str:  # command：待解析的命令字符串，返回解析后的字符串
        return command.replace('()', 'o').replace('(al)', 'al')  # 先替换空括号为 'o'，再替换 '(al)' 为 'al'，链式调用返回最终结果
