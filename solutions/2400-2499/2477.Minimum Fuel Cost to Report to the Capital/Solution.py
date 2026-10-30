# 题目：2477. 到达首都的最少油耗（Minimum Fuel Cost to Report to the Capital）
# 思路：以 0 号城市为根做一次 DFS 求每棵子树的人数；某棵子树把 sz 个人送到父节点这条边上，每辆车坐 seats 人，需要 ceil(sz/seats) 辆车也就是同样多的油，把每条边的油耗累加即答案。
# 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(n)，邻接表加递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:  # roads 是无向道路，seats 是每辆车的座位数，返回最少总油耗
        def dfs(a: int, fa: int) -> int:  # 返回以 a 为根的子树人数；fa 是父节点，用来防止往回走
            nonlocal ans  # 声明要修改外层函数里的 ans，否则 Python 会当成局部变量
            sz = 1  # 子树人数从 1 开始，即 a 自己
            for b in g[a]:  # 遍历 a 的所有邻居
                if b != fa:  # 跳过父节点，避免在树上绕圈
                    t = dfs(b, a)  # 递归求出子结点 b 那棵子树需要向上送的人数
                    ans += ceil(t / seats)  # 这些人从 b 到 a 走一条边，需要 ceil(t/seats) 辆车，也就是同样多的油
                    sz += t  # 把子树的 t 个人并入当前子树
            return sz  # 返回当前子树的总人数

        g = defaultdict(list)  # 邻接表建图
        for a, b in roads:  # 逐条读入道路
            g[a].append(b)  # 把 b 加入 a 的邻接表
            g[b].append(a)  # 把 a 加入 b 的邻接表，两条合起来构成无向图
        ans = 0  # 累计油耗，初始为 0
        dfs(0, -1)  # 从 0 号城市出发，-1 表示没有父节点
        return ans  # DFS 过程中已经把各条边的油耗累加进 ans
