# 题目：403. 青蛙过河（Frog Jump）
# 思路：记忆化 DFS。状态为「站在第 i 块石头上、上一步跳了 k 步」，下一步只能跳 k-1、k、k+1 步，用字典 pos 做值到下标映射，@cache 记住每个状态的结果。
# 时间复杂度：O(n^2)，共 n*n 个状态、每个状态枚举 3 种步长；空间复杂度：O(n^2)，缓存大小 n*n。
class Solution:  # LeetCode 约定的题解类
    def canCross(self, stones: List[int]) -> bool:  # 判断青蛙能否从第 0 块石头跳到最后一块石头
        @cache  # @cache 自动记忆化：同一个 (i, k) 只真正计算一次
        def dfs(i, k):  # dfs(i, k)：当前在 i 号石头、上一步跳了 k 步时能否到达终点
            if i == n - 1:  # 已经到最后一块石头，成功
                return True  # 返回 True
            for j in range(k - 1, k + 2):  # 下一步只能跳 k-1、k、k+1 步
                if j > 0 and stones[i] + j in pos and dfs(pos[stones[i] + j], j):  # 步长为正、落点是石头、且从落点能继续走到终点
                    return True  # 存在一条可行路径就返回 True
            return False  # 三种步长都不行，返回 False

        n = len(stones)  # n 是石头个数（闭包在后面使用，调用 dfs 时已经赋值）
        pos = {s: i for i, s in enumerate(stones)}  # 值 -> 下标 的字典，用于 O(1) 判断落点是否有石头
        return dfs(0, 0)  # 从第 0 块石头、上一步步长 0 开始搜索
