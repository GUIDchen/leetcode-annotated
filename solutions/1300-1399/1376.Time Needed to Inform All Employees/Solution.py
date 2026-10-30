# 题目：1376. 通知所有员工所需的时间（Time Needed to Inform All Employees）
# 思路：按 manager 数组建出「上级 → 下级」的树，从总负责人 headID 做一次 DFS，取所有根到叶路径耗时的最大值。
# 时间复杂度：O(n)，建图与遍历都只处理 n 个结点；空间复杂度：O(n)，邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def numOfMinutes(  # n 是员工数，headID 是总负责人，manager 记录上级，informTime 记录该员工通知下级所需时间
        self, n: int, headID: int, manager: List[int], informTime: List[int]  # 参数换行书写，避免单行过长
    ) -> int:  # 返回通知全体员工所需的时间（树形结构下路径唯一，即最长链耗时）
        def dfs(i: int) -> int:  # 内层 DFS：返回从员工 i 开始通知其子树所需的时间
            ans = 0  # 记录最慢的一条下级链的耗时
            for j in g[i]:  # 逐个处理员工 i 的直接下级
                ans = max(ans, dfs(j) + informTime[i])  # 下级 j 的耗时加上 i 通知下级所花的 informTime[i]，取其最大值
            return ans  # 返回该子树的最长耗时

        g = defaultdict(list)  # 邻接表：g[i] 存放员工 i 的直接下级
        for i, x in enumerate(manager):  # 遍历 manager 数组，建立「上级 → 下级」的边
            g[x].append(i)  # manager 中为 -1 的 headID 会落到 g[-1] 里，但 DFS 从根出发不会访问到它
        return dfs(headID)  # 从总负责人出发，返回总耗时
