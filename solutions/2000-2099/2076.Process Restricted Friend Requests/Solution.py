# 题目：2076. 处理含限制条件的好友请求（Process Restricted Friend Requests）
# 思路：并查集维护朋友连通块，对每个请求检查是否有某条禁友对恰好横跨待合并的两个集合：有则拒绝，无则同意并合并。
# 时间复杂度：O((n + |restrictions|) · |requests| · α(n))；空间复杂度：O(n)，用于并查集父数组。
class Solution:  # LeetCode 约定的题解类
    def friendRequests(  # n 是人数，restrictions 是禁友对，requests 是按顺序到来的好友请求
        self, n: int, restrictions: List[List[int]], requests: List[List[int]]  # 参数续行：self、n、restrictions、requests
    ) -> List[bool]:  # 返回每个请求是否被同意
        def find(x: int) -> int:  # 并查集查找：返回 x 所在集合的代表元
            if p[x] != x:  # 若 x 不是根节点
                p[x] = find(p[x])  # 递归找根并做路径压缩，把 x 直接挂到根上
            return p[x]  # 返回根节点

        p = list(range(n))  # 初始化并查集，p[i] 表示 i 的父节点，初始时各自成一个集合
        ans = []  # 按顺序保存每个请求的处理结果
        for u, v in requests:  # 逐个处理好友请求
            pu, pv = find(u), find(v)  # 求两人当前所在集合的代表元
            if pu == pv:  # 已在同一集合，直接同意
                ans.append(True)  # 记录 True
            else:  # 两集合不同，需要检查合并是否违反限制
                ok = True  # 先假定可以合并
                for x, y in restrictions:  # 逐条检查禁友对
                    px, py = find(x), find(y)  # 求禁友对两人所在集合的代表元
                    if (pu == px and pv == py) or (pu == py and pv == px):  # 禁友对恰好分属要合并的两个集合，合并会冲突
                        ok = False  # 标记为不合法
                        break  # 立即跳出检查
                ans.append(ok)  # 记录本次请求的判定结果
                if ok:  # 只有在没有冲突时才真正合并
                    p[pu] = pv  # 把一个集合的根挂到另一个根下
        return ans  # 返回所有请求的处理结果
