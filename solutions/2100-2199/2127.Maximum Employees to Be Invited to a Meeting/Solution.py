# 题目：2127. 参加会议的最多员工数（Maximum Employees to Be Invited to a Meeting）
# 核心思路：出度全为 1 的基环树森林。答案 = max(长度 ≥ 3 的最大纯环环长, 全部二元互惠环的两侧最长链之和)。
# 时间复杂度：O(n)，每个点只被访问常数次；空间复杂度：O(n)，vis / indeg / dist 及队列。
class Solution:  # LeetCode 约定的题解类
    def maximumInvitations(self, favorite: List[int]) -> int:  # favorite[i] 表示员工 i 最想邀请的人；返回最多能邀请的员工数
        def max_cycle(fa: List[int]) -> int:  # 内层函数：求所有纯环（长度 ≥ 3）中的最大环长
            n = len(fa)  # 员工总数
            vis = [False] * n  # vis[i] 标记员工 i 是否已经被扫过
            ans = 0  # ans 保存最大纯环长度
            for i in range(n):  # 枚举每个可能的起点
                if vis[i]:  # 已经访问过就跳过，避免重复处理同一条链/环
                    continue  # 直接进入下一个起点
                cycle = []  # cycle 按访问顺序保存本次走过的路径
                j = i  # j 表示当前走到的员工
                while not vis[j]:  # 顺着 favorite 指针一直走，直到遇到重复点（说明绕进了环）
                    cycle.append(j)  # 把当前员工记入路径
                    vis[j] = True  # 标记为已访问
                    j = fa[j]  # 沿「最喜欢的人」继续走一步
                for k, v in enumerate(cycle):  # 在本条路径中定位环的入口 j
                    if v == j:  # 路径上等于终点 j 的位置，就是环的起点
                        ans = max(ans, len(cycle) - k)  # 环长 = 整条路径长度 - 入口之前的长度
                        break  # 每个起点最多形成一个环，找到后跳出
            return ans  # 返回本图的最大纯环长

        def topological_sort(fa: List[int]) -> int:  # 内层函数：统计所有「二元互惠环 + 其两侧最长链」能坐下的人数总和
            n = len(fa)  # 员工总数
            indeg = [0] * n  # indeg[i]：有多少人最喜欢员工 i（入度）
            dist = [1] * n  # dist[i]：以 i 为起点的链长，初始只有自己，长度为 1
            for v in fa:  # 遍历 favorite 数组累计入度
                indeg[v] += 1  # 员工 v 又被喜欢了一次
            q = deque(i for i, v in enumerate(indeg) if v == 0)  # 入度为 0 的点是链末端，作为拓扑排序的起点入队
            while q:  # 不断删边推进，直到所有非环部分都被处理完
                i = q.popleft()  # 取出队首员工
                dist[fa[i]] = max(dist[fa[i]], dist[i] + 1)  # 用 i 的链长加 1 更新它的上级 fa[i] 的最长链长
                indeg[fa[i]] -= 1  # 删掉 i 指向 fa[i] 的一条入边
                if indeg[fa[i]] == 0:  # 入度减到 0 说明 fa[i] 的下游都处理完了
                    q.append(fa[i])  # 把 fa[i] 入队，继续向上推进
            return sum(dist[i] for i, v in enumerate(fa) if i == fa[fa[i]])  # 只累加互相喜欢的二元环：i 与 fa[i] 互指时把 i 这一侧的链长计入

        return max(max_cycle(favorite), topological_sort(favorite))  # 两种方案取较大者：最大纯环，或全部二元环贡献之和
