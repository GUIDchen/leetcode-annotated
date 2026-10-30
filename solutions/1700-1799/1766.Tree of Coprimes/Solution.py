# 题目：1766. 互质树（Tree of Coprimes）
# 思路：先预处理 1..50 中两两互质的数对；再 DFS 遍历树，为每个值维护一条「祖先栈」（元素为节点下标 + 深度），进入节点时压栈、回溯时出栈；对当前节点枚举与 nums[i] 互质的值，取对应栈顶中最深（离自己最近）的祖先作为答案。
# 时间复杂度：O(50^2 + n * 50)，每个节点最多枚举 50 个互质候选值；空间复杂度：O(n + 50^2)，邻接表、答案数组与 51 条栈。
class Solution:  # LeetCode 约定的题解类
    def getCoprimes(self, nums: List[int], edges: List[List[int]]) -> List[int]:  # nums：每个节点的值（1..50）；edges：无向边；返回每个节点最近的互质祖先
        def dfs(i, fa, depth):  # 递归 DFS：i 是当前节点，fa 是父节点，depth 是当前深度
            t = k = -1  # t 是答案节点，k 是该祖先的深度；-1 表示还没找到
            for v in f[nums[i]]:  # 枚举所有与 nums[i] 互质的值
                stk = stks[v]  # 取出该值对应的祖先栈
                if stk and stk[-1][1] > k:  # 栈非空且栈顶深度更大，说明它比当前答案更近
                    t, k = stk[-1]  # 栈顶是 (节点下标, 深度)，一次性更新答案节点与深度
            ans[i] = t  # 记录当前节点的答案（找不到互质祖先时仍为 -1）
            for j in g[i]:  # 遍历当前节点的所有邻居
                if j != fa:  # 跳过父节点，避免沿着来路走回去
                    stks[nums[i]].append((i, depth))  # 把当前节点按 (下标, 深度) 压栈，供子树查询祖先
                    dfs(j, i, depth + 1)  # 递归处理子节点，深度加 1
                    stks[nums[i]].pop()  # 回溯：弹出当前节点，保证栈里只剩真正的祖先

        g = defaultdict(list)  # 邻接表：defaultdict 让不存在的键自动得到空列表
        for u, v in edges:  # 遍历每条无向边
            g[u].append(v)  # u 到 v 连边
            g[v].append(u)  # v 到 u 连边（无向图要双向建边）
        f = defaultdict(list)  # f[v] 保存 1..50 中所有与 v 互质的值
        for i in range(1, 51):  # 枚举第一个值 i
            for j in range(1, 51):  # 枚举第二个值 j
                if gcd(i, j) == 1:  # 最大公约数为 1 就说明 i 与 j 互质
                    f[i].append(j)  # 把 j 记入 f[i] 的候选列表
        stks = defaultdict(list)  # stks[v] 是值为 v 的节点在当前 DFS 路径上的栈
        ans = [-1] * len(nums)  # 答案数组：ans[i] 表示节点 i 最近的互质祖先
        dfs(0, -1, 0)  # 从根节点 0 开始 DFS；根没有父节点所以传 -1，深度为 0
        return ans  # 返回答案数组
