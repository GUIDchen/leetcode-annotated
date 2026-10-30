# 题目：1908. Nim 游戏 II（Game of Nim）🔒
# 思路：博弈 DP + 记忆化。状态用各堆石子的元组表示，枚举「取哪堆、取几个」，只要存在一步让对手必败则当前必胜。
# 时间复杂度：O(状态数 × 堆数 × 每堆石子数)；空间复杂度：O(状态数)，cache 保存的搜索结果。
class Solution:  # LeetCode 约定的题解类
    def nimGame(self, piles: List[int]) -> bool:  # piles：每堆石子的数量
        @cache  # 记忆化装饰器：同一个状态只计算一次
        def dfs(st):  # 递归函数：状态 st（各堆数量的元组）下先手是否必胜
            lst = list(st)  # 元组不可变，转成列表以便原地修改并回溯
            for i, x in enumerate(lst):  # 枚举取哪一堆
                for j in range(1, x + 1):  # 枚举从这堆取走 1..x 个（Nim 允许一次取任意正数）
                    lst[i] -= j  # 走出这一步
                    if not dfs(tuple(lst)):  # 对手在新局面下必败，则当前局面必胜
                        return True  # 找到必胜走法，直接返回
                    lst[i] += j  # 恢复现场，继续尝试其他取法
            return False  # 所有走法都让对手必胜，当前局面必败

        return dfs(tuple(piles))  # 从初始局面开始判断先手胜负
