# 题目：444. 序列重建（Sequence Reconstruction）
# 思路：把每个 sequences 里相邻的二元关系建成有向图，做拓扑排序；只有每一步候选入度为 0 的点都恰好一个（队列长度始终为 1），最短超序列才唯一。
# 复杂度：时间复杂度 O(n + 所有序列长度之和)，建图加拓扑排序各扫一遍；空间复杂度 O(n + 边数)。
class Solution:  # 题解类：判断 nums 是否是 sequences 的唯一最短超序列
    def sequenceReconstruction(  # nums 是候选的完整排列（1..n），sequences 是一些短子序列
        self, nums: List[int], sequences: List[List[int]]  # 参数列表续行：self 之后是 nums 与 sequences
    ) -> bool:  # 返回是否能够唯一重建
        n = len(nums)  # n 同时也是元素种类数
        g = [[] for _ in range(n)]  # 邻接表，下标 0..n-1 对应值 1..n
        indeg = [0] * n  # 每个点的入度
        for seq in sequences:  # 遍历每个子序列
            for a, b in pairwise(seq):  # pairwise 给出相邻的两两元素，一条有向边 a -> b
                a, b = a - 1, b - 1  # 值 1..n 映射成下标 0..n-1
                g[a].append(b)  # 记录有向边
                indeg[b] += 1  # b 的入度加一
        q = deque(i for i, x in enumerate(indeg) if x == 0)  # 初始把所有入度为 0 的点放进双端队列
        while len(q) == 1:  # 每一步候选点都唯一，拓扑序才会唯一
            i = q.popleft()  # 取出唯一的候选点
            for j in g[i]:  # 遍历它的所有后继
                indeg[j] -= 1  # 后继入度减一
                if indeg[j] == 0:  # 减到 0 就可以作为新的候选
                    q.append(j)  # 入队
        return len(q) == 0  # 队列空说明所有点都被唯一地依次取出，答案唯一
