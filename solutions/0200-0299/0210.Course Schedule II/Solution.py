# 题目：210. 课程表 II（Course Schedule II）
# 思路：Kahn 拓扑排序。先修关系建有向图并统计入度，入度为 0 的课入队，出队的顺序就是合法的学习顺序。
# 时间复杂度：O(n + m)，n 为课程数、m 为先修关系数；空间复杂度：O(n + m)，需要邻接表、入度数组和结果列表。
class Solution:  # LeetCode 约定的题解类
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:  # numCourses 是课程总数，prerequisites[i] = [a, b] 表示修 a 之前必须先修 b
        g = defaultdict(list)  # 邻接表：g[b] 存放所有以 b 为先修课的课程，即 b -> a 的有向边
        indeg = [0] * numCourses  # 入度数组：indeg[a] 表示课程 a 还有多少门先修课没完成
        for a, b in prerequisites:  # 遍历每一条先修关系建图
            g[b].append(a)  # 建一条 b -> a 的有向边
            indeg[a] += 1  # a 的入度加一
        ans = []  # 按拓扑序记录学习顺序
        q = deque(i for i, x in enumerate(indeg) if x == 0)  # 双端队列：初始放入所有入度为 0 的课程
        while q:  # 队列非空就继续：每弹出一门课就把它排进顺序
            i = q.popleft()  # 取出队首课程
            ans.append(i)  # 这门课可以上了，追加到学习顺序末尾
            for j in g[i]:  # 遍历它的所有后继课程
                indeg[j] -= 1  # 后继课程入度减一
                if indeg[j] == 0:  # 减到 0 说明先修课全部完成
                    q.append(j)  # 入队，等待被学习
        return ans if len(ans) == numCourses else []  # 全部课程都排进顺序才说明无环；否则有环，按题意返回空列表
