# 题目：316. 去除重复字母（Remove Duplicate Letters）
# 思路：贪心 + 单调栈。记录每个字符最后出现的位置，扫描时若栈顶字符更大且后面还会出现，就把它弹掉，并记录已入栈字符去重。
# 时间复杂度：O(n)，每个字符最多入栈、出栈一次；空间复杂度：O(1)，字符集固定为小写字母。
class Solution:  # LeetCode 约定的题解类
    def removeDuplicateLetters(self, s: str) -> str:  # s：输入字符串
        last = {c: i for i, c in enumerate(s)}  # 每个字符最后一次出现的下标
        stk = []  # 单调栈：维护当前字典序最小的结果
        vis = set()  # 记录哪些字符已经在栈中，用于去重
        for i, c in enumerate(s):  # 从左到右扫描字符串
            if c in vis:  # 字符已在栈中，属于重复出现，直接跳过
                continue
            while stk and stk[-1] > c and last[stk[-1]] > i:  # 栈顶更大且后面还会再出现，就弹掉它让位给更小的当前字符
                vis.remove(stk.pop())  # 弹出栈顶并清除其入栈标记
            stk.append(c)  # 把当前字符压入栈
            vis.add(c)  # 标记该字符已入栈
        return ''.join(stk)  # 栈内即为字典序最小且去重的结果
