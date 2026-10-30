# 题目：4015. 树的加权和（Weighted Sum of a Tree）
# 思路：按 parent 建邻接表，用 BFS 逐层遍历（根为第 1 层，层号即深度）；遍历时先按 nums[i]*(1-d) 累加，结束后再把层数 d（等于树高 h）乘上节点值总和补回，等价于每个节点乘上 (h-d+1)。
# 时间复杂度：O(n)，每个节点入队出队各一次；空间复杂度：O(n)，邻接表与分层队列各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def weightedSum(self, parent: list[int], nums: list[int]) -> int:  # parent：父节点数组（parent[0] = -1，树以 0 为根）；nums：节点值；返回按 nums[i]*(h-d+1) 求得的加权和
        n = len(nums)  # 节点总数 n，编号为 0..n-1
        g = [[] for _ in range(n)]  # 邻接表 g：只保存父节点指向子节点的边，供自上而下分层遍历
        for i in range(1, n):  # 从 1 号节点开始建边（parent[0] = -1 不参与）
            g[parent[i]].append(i)  # 把子节点 i 挂到父节点 parent[i] 的孩子列表里
        ans = 0  # ans 累计加权和
        q = [0]  # BFS 队列，根节点 0 入队作为第 1 层
        d = 0  # d 记录当前层号；根节点深度为 1，处理第 d 层时 d 正好等于深度
        while q:  # 逐层向外扩展，直到队列为空（整棵树遍历完）
            d += 1  # 进入新的一层，层号（即深度）加一
            nq = []  # 存放下一层的全部节点
            for i in q:  # 遍历当前层的每个节点
                ans += nums[i] * (1 - d)  # 先记 nums[i]*(1-d)，相当于预扣 d*nums[i]，留到最后统一补回
                nq.extend(g[i])  # 把所有子节点一次性拼入下一层队列
            q = nq  # 队列整体切换到下一层
        ans += d * sum(nums)  # 循环结束时 d 恰好等于树高 h，补上 d*sum(nums)，与 -d*nums[i] 抵消后每个节点乘上 (h-d+1)
        return ans  # 返回加权和
