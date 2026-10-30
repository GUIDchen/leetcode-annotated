# 题目：2140. 解决智力问题（Solving Questions With Brainpower）
# 思路：记忆化搜索，dfs(i) 表示从第 i 题起能拿到的最大分数；做第 i 题得 p 分并跳到 i+b+1，不做则跳到 i+1，取较大者。
# 时间复杂度：O(n)，每个状态只计算一次；空间复杂度：O(n)，缓存表与深度为 O(n) 的递归栈。
class Solution:  # LeetCode 约定的题解类
    def mostPoints(self, questions: List[List[int]]) -> int:  # questions[i] = [分数 p, 需要跳过的题数 b]
        @cache  # 缓存 dfs 的返回值，等价于记忆化数组（同一状态只算一次）
        def dfs(i: int) -> int:  # dfs(i)：从第 i 题开始能获得的最大分数
            if i >= len(questions):  # 越界说明已经没有题可做
                return 0  # 得分为 0
            p, b = questions[i]  # 拆出本题分数 p 与需要跳过的题数 b
            return max(p + dfs(i + b + 1), dfs(i + 1))  # 二选一取较大者：做本题则跳到 i+b+1，不做则跳到 i+1

        return dfs(0)  # 从第 0 题开始求解
