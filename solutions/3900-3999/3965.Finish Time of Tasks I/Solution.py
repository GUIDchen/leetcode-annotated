# 3965. 任务完成时间 I / Finish Time of Tasks I
# 核心思路：建出以 0 为根的树后自底向上 DFS 求每个任务的完成时间：叶子取 baseTime[i]，
#          非叶子先求子任务完成时间的最小值 earliest 与最大值 latest，自身耗时 = (latest-earliest) + baseTime[i]，完成时间为 latest + 自身耗时。
# 复杂度：时间 O(n)（每个任务只访问一次），空间 O(n)（邻接表与递归栈）。

class Solution:
    def finishTime(self, n: int, edges: List[List[int]], baseTime: List[int]) -> int:  # 返回根任务 0 的完成时间
        def dfs(i: int) -> int:  # 递归求任务 i 的完成时间
            if not g[i]:  # 叶子任务没有子任务
                return baseTime[i]  # 叶子完成时间就是自身耗时
            earliest, latest = inf, -inf  # 子任务完成时间的最小值与最大值，先用正负无穷初始化
            for j in g[i]:  # 遍历任务 i 的每个子任务
                a = dfs(j)  # 递归得到子任务 j 的完成时间
                earliest = min(earliest, a)  # 更新最早的子任务完成时间
                latest = max(latest, a)  # 更新最晚的子任务完成时间
            own_duration = (latest - earliest) + baseTime[i]  # 自身耗时：等待跨度加上基础耗时
            return latest + own_duration  # 完成时间 = 最晚子任务完成时间 + 自身耗时

        g = [[] for _ in range(n)]  # 邻接表，g[u] 存放任务 u 的所有子任务
        for u, v in edges:  # 遍历每条父子边
            g[u].append(v)  # 记录任务 u 的子任务是 v
        return dfs(0)  # 从根任务 0 开始计算并返回其完成时间
