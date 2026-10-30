# 题目：2973. 树中每个节点放置的金币数目（Find Number of Coins to Place in Tree Nodes）
# 思路：建无向图后自底向上 DFS，子树花费排序，节点答案取最大三数之积与「最小两负数乘最大数」的较大者；向上只回传 2 个最小值与 3 个最大值。
# 时间复杂度：O(n log n)；空间复杂度：O(n)（邻接表、递归栈）。
class Solution:  # LeetCode 约定的题解类
    def placedCoins(self, edges: List[List[int]], cost: List[int]) -> List[int]:  # edges：树的边；cost：每个节点的花费；返回每个节点的金币数目
        def dfs(a: int, fa: int) -> List[int]:  # 内部递归函数：返回以 a 为根的子树中排序后的花费列表，fa 是父节点
            res = [cost[a]]  # 先放入自己的花费
            for b in g[a]:  # 遍历所有邻居
                if b != fa:  # 跳过父节点，避免走回头路（根的父节点用 -1 表示）
                    res.extend(dfs(b, a))  # 把子树返回的列表并入当前列表
            res.sort()  # 排序：最小值在前、最大值在后，方便取极值
            if len(res) >= 3:  # 至少 3 个节点才能放 3 枚金币
                ans[a] = max(res[-3] * res[-2] * res[-1], res[0] * res[1] * res[-1], 0)  # 取三种乘积的较大者再与 0 比较：最大三个、最小两个负数乘最大数、以及兜底 0
            if len(res) > 5:  # 只需极值即可覆盖所有最优组合，多于 5 个时裁剪
                res = res[:2] + res[-3:]  # 保留最小两个与最大三个，向上回传
            return res  # 返回给父节点合并

        n = len(cost)  # n 为节点个数
        g = [[] for _ in range(n)]  # 邻接表初始化：g[v] 保存 v 的邻居列表
        for a, b in edges:  # 遍历每条边建双向连接
            g[a].append(b)  # a 的邻居加入 b
            g[b].append(a)  # b 的邻居加入 a，构成无向图
        ans = [1] * n  # 答案数组默认 1：不足 3 个节点时放 1 枚金币
        dfs(0, -1)  # 从根节点 0 开始 DFS，-1 表示没有父节点
        return ans  # 返回每个节点的金币数目
