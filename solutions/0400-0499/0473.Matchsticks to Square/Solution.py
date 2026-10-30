# 题目：473. 火柴拼正方形（Matchsticks to Square）
# 思路：总和必须能被 4 整除且最长火柴不超过边长；把火柴降序排序后用 DFS 逐根尝试放进 4 条边，并跳过等长的重复边做剪枝。
# 时间复杂度：O(4^n) 最坏（n 为火柴数，降序加剪枝后远快于此）；空间复杂度：O(n)，递归栈深度等于火柴数。
class Solution:  # LeetCode 约定的题解类
    def makesquare(self, matchsticks: List[int]) -> bool:  # matchsticks 是每根火柴的长度
        def dfs(u):  # u 是当前要放置的火柴下标
            if u == len(matchsticks):  # 所有火柴都放完了
                return True  # 说明四条边都正好凑齐边长
            for i in range(4):  # 尝试把当前火柴放进 4 条边中的某一条
                if i > 0 and edges[i - 1] == edges[i]:  # 前一条边与当前边长度相同就跳过，避免重复枚举等价的边
                    continue  # 进入下一次循环试下一条边
                edges[i] += matchsticks[u]  # 先放进去，更新该边长度
                if edges[i] <= x and dfs(u + 1):  # 不超过边长，且剩下的火柴也能放成功
                    return True  # 整体可行，直接返回
                edges[i] -= matchsticks[u]  # 回溯：撤销这一步的放置
            return False  # 4 条边都放不下，当前分支无解

        x, mod = divmod(sum(matchsticks), 4)  # x 是正方形边长，mod 是总长对 4 的余数
        if mod or x < max(matchsticks):  # 总长不是 4 的倍数，或最长火柴超过边长
            return False  # 两种情况都无法拼成正方形
        edges = [0] * 4  # edges[i] 记录第 i 条边当前已放火柴的长度
        matchsticks.sort(reverse=True)  # 降序排序：先放长火柴，能更早触发剪枝
        return dfs(0)  # 从第 0 根火柴开始回溯搜索
