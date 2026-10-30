# 题目：682. 棒球比赛（Baseball Game）
# 思路：用列表当栈按顺序保存每一轮的有效得分，"+" 取前两轮之和、"D" 取上一轮两倍、"C" 撤销上一轮，最后求和。
# 时间复杂度：O(n)，每条记录只处理一次；空间复杂度：O(n)，栈最多保存 n 个得分。
class Solution:  # LeetCode 约定的题解类
    def calPoints(self, operations: List[str]) -> int:  # operations 是按顺序给出的操作列表
        stk = []  # 用列表模拟栈，只保存当前有效的各轮得分
        for op in operations:  # 逐条处理操作记录
            if op == "+":  # 新得分等于前两轮得分之和
                stk.append(stk[-1] + stk[-2])  # 取末尾两个有效得分相加后入栈
            elif op == "D":  # 新得分等于上一轮得分的两倍
                stk.append(stk[-1] << 1)  # 左移一位相当于乘 2
            elif op == "C":  # 撤销上一轮的得分
                stk.pop()  # 弹出栈顶，让那一轮得分失效
            else:  # 其余情况是数字字符串，表示本轮直接得分
                stk.append(int(op))  # 转成整数后入栈
        return sum(stk)  # 栈内所有有效得分之和就是最终得分
