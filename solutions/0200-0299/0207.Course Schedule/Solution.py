# 题目：207. 课程表（Course Schedule）
# 思路：Kahn 拓扑排序。先修关系建有向图并统计入度，入度为 0 的课入队，逐个出队消边，最后看能否修完全部课程。
# 时间复杂度：O(n + m)，n 为课程数、m 为先修关系数；空间复杂度：O(n + m)，需要邻接表和入度数组。
class Solution:  # LeetCode 约定的题解类
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:  # numCourses 是课程总数，prerequisites[i] = [a, b] 表示修 a 之前必须先修 b
        g = [[] for _ in range(numCourses)]  # 邻接表：g[b] 存放所有以 b 为先修课的课程 a，即 b -> a 的有向边
        indeg = [0] * numCourses  # 入度数组：indeg[a] 表示课程 a 还有多少门先修课没完成
        for a, b in prerequisites:  # 遍历每一条先修关系建图
            g[b].append(a)  # 建一条 b -> a 的有向边
            indeg[a] += 1  # a 的入度加一
        q = [i for i, x in enumerate(indeg) if x == 0]  # 队列（这里用列表实现）：初始放入所有入度为 0 的课程
        for i in q:  # 依次处理队列中的课程；循环途中 append 进来的元素同样会被遍历到
            numCourses -= 1  # 相当于修完一门课，未完成课程数减一
            for j in g[i]:  # 遍历这门课的所有后继课程
                indeg[j] -= 1  # 后继课程入度减一
                if indeg[j] == 0:  # 减到 0 说明先修课全部完成
                    q.append(j)  # 入队，等待被修
        return numCourses == 0  # 全部课程都被修完说明不存在环，可以完成全部课程
