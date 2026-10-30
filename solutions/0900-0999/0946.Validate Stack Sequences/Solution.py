# 题目：946. 验证栈序列（Validate Stack Sequences）
# 思路：按 pushed 顺序入栈，每入一个就尽量按 popped 的顺序从栈顶弹出；最后检查 popped 是否被完整走完。
# 时间复杂度：O(n)，每个元素入栈、出栈各至多一次；空间复杂度：O(n)，栈最多同时保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:  # pushed 是入栈顺序，popped 是待验证的出栈顺序
        stk = []  # 用列表当栈，末尾即栈顶
        i = 0  # 指向 popped 中下一个应当被弹出的位置
        for x in pushed:  # 按 pushed 的顺序依次压栈
            stk.append(x)  # 当前元素入栈，这是模拟中唯一允许的入栈动作
            while stk and stk[-1] == popped[i]:  # 栈非空且栈顶正好等于下一个期望值时，才允许连续弹出
                stk.pop()  # 执行一次出栈
                i += 1  # 期望值前进一位
        return i == len(popped)
