# 题目：2092. 找出知晓秘密的所有专家（Find All People With Secret）
# 思路：按会议时间升序分组，逐个时间片建临时图，从「已知情」的人做 BFS 向同一时间片的人传播秘密。
# 时间复杂度：O(m log m + m)，排序 m 场会议后每场只处理常数次；空间复杂度：O(n + m)，vis 数组与时间片临时图。
class Solution:  # LeetCode 约定的题解类
    def findAllPeople(  # 返回所有最终知晓秘密的人的编号列表
        self, n: int, meetings: List[List[int]], firstPerson: int  # self：实例；n：人数；meetings：{a, b, t} 三元组；firstPerson：第一个得知秘密的人
    ) -> List[int]:  # 返回值是知情者编号列表
        vis = [False] * n  # vis[i] 表示编号 i 是否已知晓秘密，默认全为 False
        vis[0] = vis[firstPerson] = True  # 0 号本人与 firstPerson 一开始就知情
        meetings.sort(key=lambda x: x[2])  # 按时间（每场会议的第 3 个元素）升序排序，同时间的会议因此相邻
        i, m = 0, len(meetings)  # i 是当前时间段的起点，m 是会议总数
        while i < m:  # 逐个时间段处理
            j = i  # j 用来向右寻找同一时间的段尾
            while j + 1 < m and meetings[j + 1][2] == meetings[i][2]:  # 下一场会议时间仍相同就继续右扩
                j += 1  # 段尾右移，循环结束后 [i, j] 内会议时间全相等
            s = set()  # 本时间片出现的人员集合，用来挑 BFS 的种子
            g = defaultdict(list)  # 本时间片的临时邻接表：只装这一时间段内的边
            for x, y, _ in meetings[i : j + 1]:  # 遍历本时间片的每一场会议（第 3 个元素时间用不上，用 _ 忽略）
                g[x].append(y)  # 建 x -> y 的无向边
                g[y].append(x)  # 建 y -> x 的无向边
                s.update([x, y])  # 参会两人都记入本时间片的人员集合
            q = deque([u for u in s if vis[u]])  # 只把已知情的人作为 BFS 起点，双端队列支持 O(1) 出队
            while q:  # 在本时间片的图里做 BFS
                u = q.popleft()  # 从队首取出一个人
                for v in g[u]:  # 枚举与 u 在同一时间片开过会的人
                    if not vis[v]:  # 尚未知情才需要更新
                        vis[v] = True  # 标记为知情
                        q.append(v)  # 继续向外扩散
            i = j + 1  # 跳过本时间片，处理下一个时间段
        return [i for i, v in enumerate(vis) if v]  # 按编号顺序收集所有知情者，天然有序
