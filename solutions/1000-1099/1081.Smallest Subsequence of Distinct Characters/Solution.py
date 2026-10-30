# 题目：1081. 不同字符的最小子序列（Smallest Subsequence of Distinct Characters）
# 思路：先用字典记录每个字符最后出现的下标，再用单调栈构造答案：字符已在栈中则跳过，否则反复弹出「比当前字符大且后面还会出现」的栈顶，保证字典序最小且每个字符只出现一次。
# 时间复杂度：O(n)，每个字符最多入栈、出栈各一次；空间复杂度：O(1)，栈与集合最多只含 26 个字符。
class Solution:  # LeetCode 约定的题解类
    def smallestSubsequence(self, s: str) -> str:  # s 是原字符串（全小写字母）
        last = {c: i for i, c in enumerate(s)}  # 字典推导：记录每个字符最后出现的下标（后出现的会覆盖前面的）
        stk = []  # 单调栈：保存当前构造出的、字典序尽量小的子序列
        vis = set()  # 记录已经进入栈中的字符，用于去重
        for i, c in enumerate(s):  # 从左到右逐个处理原串字符
            if c in vis:  # 该字符已经在栈里，重复加入会破坏「每个字符恰好一次」
                continue  # 直接跳过这个字符
            while stk and stk[-1] > c and last[stk[-1]] > i:  # 栈顶更大且后面还会再次出现，就可以先弹掉换成更小的 c
                vis.remove(stk.pop())  # 弹出栈顶并同时把它从已用集合中移除
            stk.append(c)  # 把当前字符压入栈
            vis.add(c)  # 标记该字符已进入答案
        return "".join(stk)  # 栈内字符顺序即字典序最小的不同字符子序列，拼接成字符串返回
