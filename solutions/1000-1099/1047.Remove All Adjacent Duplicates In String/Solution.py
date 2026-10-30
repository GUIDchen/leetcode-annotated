# 题目：1047. 删除字符串中的所有相邻重复项（Remove All Adjacent Duplicates In String）
# 思路：用列表当字符栈从左到右扫描，当前字符与栈顶相同就弹栈（成对删除），否则入栈。
# 时间复杂度：O(n)，每个字符最多入栈出栈一次；空间复杂度：O(n)，栈最多保存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def removeDuplicates(self, s: str) -> str:  # s：输入字符串；返回删除相邻重复对后的结果
        stk = []  # 用列表模拟栈，stk[-1] 就是栈顶
        for c in s:  # 从左到右扫描，保证新形成的相邻重复也能被发现
            if stk and stk[-1] == c:  # 栈非空且栈顶与当前字符相同
                stk.pop()  # 弹出栈顶，相当于把这一对一起删掉
            else:  # 不构成重复对，需要入栈
                stk.append(c)  # 当前字符入栈
        return ''.join(stk)  # 列表转成字符串即为答案
