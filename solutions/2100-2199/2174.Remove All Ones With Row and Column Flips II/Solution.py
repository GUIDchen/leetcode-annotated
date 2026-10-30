# 题目：2174. 通过翻转行或列来去除所有的 1 II（Remove All Ones With Row and Column Flips II）
# 思路：把网格压缩成一个整数位掩码做 BFS；每步对某个原本为 1 的格子所在的行与列清零，首次遇到 0 状态的层数就是答案。
# 时间复杂度：O(2^(m·n) · m·n·(m+n))，状态数最多 2^(m·n)；空间复杂度：O(2^(m·n))，deque 与 visited 集合。
class Solution:  # LeetCode 约定的题解类
    def removeOnes(self, grid: List[List[int]]) -> int:  # grid 是 0/1 网格；返回清空所有 1 的最少操作数，无解时返回 -1
        m, n = len(grid), len(grid[0])  # m 行 n 列；位号 i*n+j 对应第 i 行第 j 列
        state = sum(1 << (i * n + j) for i in range(m) for j in range(n) if grid[i][j])  # 把值为 1 的格子对应的位累加进 state（各位互不重叠，求和等价于按位或），得到初始状态
        q = deque([state])  # 双端队列初始只有初始状态，作为 BFS 的第 0 层
        vis = {state}  # visited 集合，防止同一状态被重复入队
        ans = 0  # 当前 BFS 层数，等价于已经执行过的操作次数
        while q:  # 队列非空就继续扩展
            for _ in range(len(q)):  # 逐层扩展：先固定本层节点个数，避免把新加入的节点也算进同一层
                state = q.popleft()  # 弹出队首状态
                if state == 0:  # 状态为 0 表示所有 1 都已清除
                    return ans  # 当前层数就是最少操作次数，直接返回
                for i in range(m):  # 枚举行，寻找可以作为操作中心的 1
                    for j in range(n):  # 枚举列
                        if grid[i][j] == 0:  # 原网格该位置不是 1，不能以它为中心清行清列
                            continue  # 跳过这个格子
                        nxt = state  # 复制当前状态，准备生成下一状态
                        for r in range(m):  # 把第 j 列整列清零：逐行清除 (r, j) 对应的位
                            nxt &= ~(1 << (r * n + j))  # 按位与非，把这一位变成 0
                        for c in range(n):  # 把第 i 行整行清零：逐列清除 (i, c) 对应的位
                            nxt &= ~(1 << (i * n + c))  # 同样按位与非清掉这一位
                        if nxt not in vis:  # 新状态没有被访问过才入队
                            vis.add(nxt)  # 标记为已访问
                            q.append(nxt)  # 加入队列，等待下一层扩展
            ans += 1  # 本层所有节点扩展完毕，层数加一，相当于多做一次操作
        return -1  # 所有可达状态都试过仍未清空，说明无解，返回 -1
