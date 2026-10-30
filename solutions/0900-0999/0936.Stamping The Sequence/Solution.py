# 题目：936. 戳印序列（Stamping The Sequence）
# 思路：反向拓扑排序（BFS）。把每个盖章起点当作节点，入度是还需要被覆盖的错位数；入度为 0 表示此刻就能盖，盖章后再解锁依赖这些位置的节点。
# 时间复杂度：O(n*m)，每个盖章位置与每个字符位置各处理常数次；空间复杂度：O(n*m)，邻接表的总规模。
class Solution:  # LeetCode 约定的题解类
    def movesToStamp(self, stamp: str, target: str) -> List[int]:  # stamp 是印章，target 是目标串；返回每次盖章的起始下标序列，无解则返回空
        m, n = len(stamp), len(target)  # m 是印章长度，n 是目标串长度
        indeg = [m] * (n - m + 1)  # indeg[i]：以 i 为起点盖章时，还有多少个位置不匹配、需要被之前的某次盖章覆盖
        q = deque()  # 入度为 0 的盖章起点，表示现在就能盖
        g = [[] for _ in range(n)]  # g[p] 保存所有会覆盖到位置 p 的盖章起点
        for i in range(n - m + 1):  # 枚举所有合法的盖章起点
            for j, c in enumerate(stamp):  # 同时取出印章中的偏移 j 与字符 c
                if target[i + j] == c:  # 该位置本来就与印章一致，不需要被覆盖
                    indeg[i] -= 1  # 匹配的位置不贡献入度
                    if indeg[i] == 0:  # 减到 0 说明所有位置都匹配，此刻可以盖章
                        q.append(i)  # 起点入队
                else:
                    g[i + j].append(i)  # 该位置不匹配，要靠之前某次覆盖到它的盖章来补齐
        ans = []  # 把起点 i 登记到位置 i+j 的依赖表里
        vis = [False] * n  # ans 逆序记录盖章的起点
        while q:  # vis[p]：目标串第 p 个位置是否已经被某次盖章覆盖成正确字符
            i = q.popleft()  # 队列非空就一直取「现在能盖」的起点
            ans.append(i)  # 取出队首
            for j in range(m):  # 记录这次盖章
                if not vis[i + j]:  # 这次盖章会覆盖 stamp 的每个位置
                    vis[i + j] = True  # 同一位置只需处理一次，重复覆盖不会带来新信息
                    for k in g[i + j]:  # 标记该位置已变正确
                        indeg[k] -= 1  # 所有依赖这个位置的盖章起点，入度都可以减一
                        if indeg[k] == 0:  # 入度减到 0，说明该起点现在也能盖了
                            q.append(k)  # 入队
        return ans[::-1] if all(vis) else []  # 拓扑序是「最后盖的在前」，翻转后才是正向顺序；有位置没被覆盖就返回空表示无解
