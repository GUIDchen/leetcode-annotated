# 题目：2696. 删除子串后的字符串最小长度（Minimum String Length After Removing Substrings）
# 核心思路：用列表当栈，扫描每个字符，若它与栈顶能组成 "AB" 或 "CD" 就弹出栈顶（成对消去），否则入栈；栈自动处理反复消去的连锁反应。
# 时间复杂度：O(n)，每个字符最多入栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def minLength(self, s: str) -> int:  # s：只含 'A'、'B'、'C'、'D' 的字符串；返回无法再消去的最短长度
        stk = [""]  # 用列表模拟栈，先放一个空串哨兵，保证 stk[-1] 永远不会越界
        for c in s:  # 依次处理每个字符
            if (c == "B" and stk[-1] == "A") or (c == "D" and stk[-1] == "C"):  # 当前字符与栈顶恰好组成 "AB" 或 "CD"，可以成对消去
                stk.pop()  # 弹出栈顶字符，当前字符也不再入栈，相当于两者一起消失
            else:  # 凑不成可消子串
                stk.append(c)  # 入栈，等待后续字符来配对
        return len(stk) - 1  # 减掉哨兵，得到最终无法消去的最短长度
