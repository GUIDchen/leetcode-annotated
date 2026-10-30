# 题目：2050. 并行课程 III（Parallel Courses III）
# 思路：把先修关系建成有向图，拓扑排序的同时做最长路 DP：f[i] = time[i] + max(f[前驱])，答案取所有 f 的最大值。
# 时间复杂度：O(n + m)，n 为课程数、m 为先修关系数；空间复杂度：O(n + m)，邻接表、入度数组与 DP 数组。
class Solution:  # 题解类
    def minimumTime(self, n: int, relations: List[List[int]], time: List[int]) -> int:  # n 门课程；relations 是先修关系；time 是每门课的耗时
        g = defaultdict(list)  # 邻接表：g[a] 存放所有以 a 为先修课的课程
        indeg = [0] * n  # indeg[i] 表示课程 i 还缺多少个先修课
        for a, b in relations:  # 遍历每条先修关系（课程编号从 1 开始）
            g[a - 1].append(b - 1)  # 减 1 转成 0 下标后连边
            indeg[b - 1] += 1  # 后继课 b 的入度加一
        q = deque()  # 拓扑排序队列，存当前所有可修课程
        f = [0] * n  # f[i] 表示课程 i 修完的最早月份
        ans = 0  # ans 记录所有课程完成时刻的最大值，即最终答案
        for i, (v, t) in enumerate(zip(indeg, time)):  # 同时取入度与耗时，找出初始可修课程
            if v == 0:  # 入度为 0 说明没有先修课
                q.append(i)  # 入队，稍后用它更新后继课程
                f[i] = t  # 它的最早完成时间就是自身耗时
                ans = max(ans, t)  # 用它的完成时间更新全局答案
        while q:  # 队列非空说明还有课程可以继续推进
            i = q.popleft()  # 取队首课程编号
            for j in g[i]:  # 遍历以 i 为先修课的后继课程 j
                f[j] = max(f[j], f[i] + time[j])  # 状态转移：j 必须等 i 修完才能开始，取较晚者
                ans = max(ans, f[j])  # 用 j 的完成时间更新全局答案
                indeg[j] -= 1  # 消耗 j 的一条依赖
                if indeg[j] == 0:  # 依赖都满足，j 可以修了
                    q.append(j)  # 入队
        return ans  # 返回所有课程的最晚完成时间
