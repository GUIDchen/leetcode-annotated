# 题目：2440. 创建价值相同的连通块（Create Components With Same Value）【困难】
# 思路：总和为 s，若切成 k 块则每块价值和必须等于 t = s // k；从 min(n, s // mx) 递减枚举 k，只对 s % k == 0 的 k 做一次后序 DFS 自底向上切块，成功即返回 k - 1。
# 时间复杂度：最坏 O(n·min(n, s//mx))，只有 s % k == 0 时才做一次 O(n) 的 DFS；空间复杂度：O(n)，邻接表 + 递归栈。
class Solution:  # LeetCode 约定的题解类
    def componentValue(self, nums: List[int], edges: List[List[int]]) -> int:  # nums 是各节点价值，edges 是无向树的边
        def dfs(i, fa):  # 后序 DFS：返回以 i 为根的未封口块价值和，-1 表示这种切法不合法（g 与 t 在后面才赋值，靠闭包引用，调用时已存在）
            x = nums[i]  # 当前块先放入节点 i 自身的价值
            for j in g[i]:  # 遍历 i 的邻居
                if j != fa:  # 跳过父节点 fa，避免沿树边绕回去
                    y = dfs(j, i)  # 递归处理子树 j，并把 i 作为它的父节点传入
                    if y == -1:  # 子树已判定失败
                        return -1  # 整棵子树立刻失败上抛
                    x += y  # 把子树送回来的残留价值和并入当前块
            if x > t:  # 当前块和超过目标 t，已经无法补救
                return -1  # 返回 -1 表示这种切法非法
            return x if x < t else 0  # 正好等于 t 就封口返回 0；不足 t 就把残留 x 交给父节点继续累加

        n = len(nums)  # 节点个数，块数 k 的上界之一
        g = defaultdict(list)  # 邻接表：节点 -> 邻居列表（defaultdict 省去判空建表）
        for a, b in edges:  # 逐条边建无向图
            g[a].append(b)  # a 的邻居列表追加 b
            g[b].append(a)  # b 的邻居列表追加 a（无向图双向都要加）
        s = sum(nums)  # 全部节点价值之和
        mx = max(nums)  # 单节点最大价值，决定块数上界 s // mx
        for k in range(min(n, s // mx), 1, -1):  # 从可能的最大块数递减枚举 k；k = 1 时答案是 0，不必尝试
            if s % k == 0:  # 只有总和能被 k 整除，每块才可能分到整数价值和
                t = s // k  # 计算本次尝试的目标块和
                if dfs(0, -1) == 0:  # 从 0 号节点出发（父节点记 -1），返回 0 说明整棵树恰好切成 k 块
                    return k - 1  # k 块之间需要删掉 k - 1 条边，这就是答案
        return 0  # 所有 k 都失败，只能保持一整块，返回 0 条被删边
