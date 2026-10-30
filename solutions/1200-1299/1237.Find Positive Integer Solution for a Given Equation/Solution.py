# 题目：1237. 找出给定方程的正整数解（Find Positive Integer Solution for a Given Equation）
# 思路：枚举 x，利用 f 对 y 单调递增，用 bisect_left 二分出第一个使 f(x, y) >= z 的 y，再校验是否等于 z。
# 时间复杂度：O(z log z)，每个 x 一次二分；空间复杂度：O(1)，除答案外只用常数变量。
"""
This is the custom function interface.
You should not implement it, or speculate about its implementation
class CustomFunction:
    # Returns f(x, y) for any given positive integers x and y.
    # Note that f(x, y) is increasing with respect to both x and y.
    # i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
    def f(self, x, y):

"""


class Solution:  # LeetCode 约定的题解类
    def findSolution(self, customfunction: "CustomFunction", z: int) -> List[List[int]]:  # customfunction 是单调递增的 f，z 是目标和，返回所有正整数解
        ans = []  # 收集所有满足 f(x, y) == z 的解
        for x in range(1, z + 1):  # 枚举 x（题目保证解不超过 z）
            y = 1 + bisect_left(  # 对候选 y 做二分，找第一个使 f(x, y) >= z 的位置（返回的是下标）
                range(1, z + 1), z, key=lambda y: customfunction.f(x, y)  # key 让二分按 f(x, y) 的取值比较，range 只负责提供候选 y
            )  # bisect_left 的下标从 0 开始，加 1 还原成 y 的取值
            if customfunction.f(x, y) == z:  # 只有恰好等于 z 才是合法解
                ans.append([x, y])  # 记录解 [x, y]
        return ans  # 返回全部解
