# 题目：1857. 有向图中最大颜色值（Largest Color Value in a Directed Graph）
# 思路：拓扑排序 + 26 维 DP。dp[v][k] 记录以 v 结尾的路径上颜色 k 的最大出现次数，按拓扑序沿边转移并判断颜色是否相同；处理完所有结点则取全局最大值，否则图中存在环，返回 -1。
# 时间复杂度：O((n + m) × 26)，每条边做 26 次转移；空间复杂度：O(26n)，dp 表与邻接表。
class Solution:  # LeetCode 约定的题解类
    def largestPathValue(self, colors: str, edges: List[List[int]]) -> int:  # colors：各结点颜色字母；edges：有向边，求路径上同一颜色出现次数的最大值
        n = len(colors)  # n：结点个数
        indeg = [0] * n  # 入度数组，用于拓扑排序并检测环
        g = defaultdict(list)  # 邻接表，g[a] 存放 a 的所有后继
        for a, b in edges:  # 遍历每条边建图
            g[a].append(b)  # a 指向 b
            indeg[b] += 1  # b 的入度加一，建图到此结束
        q = deque()  # 拓扑排序用的双端队列（FIFO）
        dp = [[0] * 26 for _ in range(n)]  # dp[i][k]：以 i 结尾的路径上颜色 k 出现的最多次数，初始全 0
        for i, v in enumerate(indeg):  # 枚举所有结点，找出入度为 0 的起点
            if v == 0:  # 入度为 0 才能作为路径起点
                q.append(i)  # 入队
                c = ord(colors[i]) - ord('a')  # 结点颜色映射到 0..25
                dp[i][c] += 1  # 起点自身贡献一次该颜色
        cnt = 0  # cnt：已处理的结点数，判环用
        ans = 1  # ans：全局最大颜色值，只含一个结点时至少为 1
        while q:  # BFS 版拓扑排序
            i = q.popleft()  # 出队队首下标
            cnt += 1  # 统计已处理结点数
            for j in g[i]:  # 遍历 i 的所有后继
                indeg[j] -= 1  # 入度减一
                if indeg[j] == 0:  # 入度归零说明所有前驱都处理完，可以入队
                    q.append(j)  # 入队等待处理
                c = ord(colors[j]) - ord('a')  # j 的颜色下标
                for k in range(26):  # 对 26 种颜色逐一转移
                    dp[j][k] = max(dp[j][k], dp[i][k] + (c == k))  # 继承 dp[i][k]，若 j 的颜色正好是 k 则再加 1
                    ans = max(ans, dp[j][k])  # 更新全局答案
        return -1 if cnt < n else ans  # cnt == n 表示无环，返回答案；否则有环，返回 -1
