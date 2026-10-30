# 题目：3991. Sort Array Using Prefix Reversals（3991. 使用前缀反转对数组进行排序）
# 核心思路：把排列状态当作节点做 BFS，每一步可用 pre 中任意长度做前缀反转；状态用元组直接哈希去重，第一次到达升序状态时的层数就是最少反转次数。
# 复杂度：时间 O(n!·|pre|)，空间 O(n!)（最坏遍历所有排列）。
class Solution:  # 定义题解类
    def sortArray(self, nums: List[int], pre: List[int]) -> int:  # 返回用 pre 中的前缀长度把 nums 反转成升序所需的最少操作次数
        n = len(nums)  # n 为数组长度
        target = tuple(range(n))  # 升序目标状态 (0, 1, …, n-1)
        start = tuple(nums)  # 初始状态转成元组，便于哈希与不可变比较

        if start == target:  # 初始已是升序
            return 0  # 不需要任何操作

        vis = {start}  # vis 记录已访问的状态，避免重复搜索
        q = deque([(start, 0)])  # BFS 队列，元素为 (状态, 已用操作次数)

        while q:  # 队列非空就继续搜索
            state, dist = q.popleft()  # 取出队首的状态与操作次数
            nd = dist + 1  # 扩展到下一层，操作次数加一
            for x in pre:  # 逐个尝试 pre 中允许的前缀长度
                nxt = state[:x][::-1] + state[x:]  # 前 x 个元素反转后接上剩余部分，得到新状态
                if nxt == target:  # 首次到达升序状态，层数即最少操作次数
                    return nd  # 返回该层对应的操作次数
                if nxt not in vis:  # 该状态尚未访问过
                    vis.add(nxt)  # 标记为已访问
                    q.append((nxt, nd))  # 入队等待继续扩展
        return -1  # BFS 结束仍未到达升序，说明无法排序
