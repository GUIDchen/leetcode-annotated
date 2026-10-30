# 题目：1249. 移除无效的括号（Minimum Remove to Make Valid Parentheses）
# 思路：两遍扫描 —— 先从左往右删掉多余的右括号，再从右往左删掉多余的左括号，最后翻转得到结果。
# 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(n)，用于存中间结果与答案。
class Solution:  # LeetCode 约定的题解类
    def minRemoveToMakeValid(self, s: str) -> str:  # 删除最少数量的括号，使剩下的字符串括号合法
        stk = []  # 用列表当栈，保存正向扫描后保留下来的字符
        x = 0  # 当前还未匹配的左括号数量
        for c in s:  # 从左往右扫描每个字符
            if c == ')' and x == 0:  # 没有左括号可以配对的右括号
                continue  # 直接丢弃这个右括号
            if c == '(':  # 左括号
                x += 1  # 待匹配的左括号加一
            elif c == ')':  # 右括号
                x -= 1  # 与一个左括号配对，待匹配数减一
            stk.append(c)  # 保留该字符
        x = 0  # 复用计数器，这一遍统计未匹配的右括号
        ans = []  # 反向扫描得到的结果（追加顺序是逆序）
        for c in stk[::-1]:  # 从后往前遍历剩余字符
            if c == '(' and x == 0:  # 没有右括号可配对的左括号
                continue  # 丢弃它
            if c == ')':  # 右括号
                x += 1  # 待匹配的右括号加一
            elif c == '(':  # 左括号
                x -= 1  # 与一个右括号配对，待匹配数减一
            ans.append(c)  # 保留该字符
        return ''.join(ans[::-1])  # 逆序收集的答案再翻转回正序
