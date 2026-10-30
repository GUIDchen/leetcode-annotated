# 题目：2120. 执行所有后缀指令（Execution of All Suffix Instructions Staying in a Grid）
# 核心思路：把四个方向存成坐标增量，对每个后缀从起点逐个试走，越界立即停下，走过的步数就是答案。
# 时间复杂度：O(m^2)，m = len(s)，每个后缀最坏走满整个串；空间复杂度：O(m)，答案列表与常数大小的方向表。
class Solution:  # LeetCode 约定的题解类
    def executeInstructions(self, n: int, startPos: List[int], s: str) -> List[int]:  # n：网格边长；startPos：起点；s：指令串
        ans = []  # 依次收集每个后缀的执行步数
        m = len(s)  # 指令串长度，也是后缀个数
        mp = {"L": [0, -1], "R": [0, 1], "U": [-1, 0], "D": [1, 0]}  # 方向字符 → [行增量, 列增量]
        for i in range(m):  # 枚举后缀起点 i，后缀为 s[i:]
            x, y = startPos  # 每个后缀都从题给起点重新出发
            t = 0  # 这个后缀成功执行的步数
            for j in range(i, m):  # 按顺序尝试后缀中的每条指令
                a, b = mp[s[j]]  # 拆出这条指令的行增量与列增量
                if 0 <= x + a < n and 0 <= y + b < n:  # 只有走完后仍在网格内才允许走
                    x, y, t = x + a, y + b, t + 1  # 一行同时完成坐标更新与步数加一
                else:
                    break  # 走完会越界，立刻停止，后面的指令不再执行
            ans.append(t)  # 记录该后缀的答案
        return ans  # 返回所有后缀的执行步数
