# 题目：2101. 引爆最多的炸弹（Detonate the Maximum Bombs）
# 思路：i 的爆炸范围覆盖 j 就连 i → j 的有向边，再以每个点为起点做 BFS，统计可达点数取最大值。
# 时间复杂度：O(n^3)，建图 O(n^2) 加 n 次 BFS；空间复杂度：O(n^2)，邻接表存边。
class Solution:  # LeetCode 约定的题解类
    def maximumDetonation(self, bombs: List[List[int]]) -> int:  # bombs[i] = [x, y, r]，返回一次引爆能波及的最多炸弹数
        n = len(bombs)  # 炸弹总数
        g = [[] for _ in range(n)]  # 邻接表：g[i] 保存 i 能直接引爆的炸弹编号
        for i in range(n - 1):  # 枚举每一对炸弹，只取 i < j 避免重复
            x1, y1, r1 = bombs[i]  # 拆出第 i 颗炸弹的圆心与半径
            for j in range(i + 1, n):  # 枚举与 i 配对的另一颗炸弹 j
                x2, y2, r2 = bombs[j]  # 拆出第 j 颗炸弹的圆心与半径
                dist = hypot(x1 - x2, y1 - y2)  # 两圆心之间的欧氏距离
                if dist <= r1:  # 距离不超过 i 的半径，说明 i 能引爆 j
                    g[i].append(j)  # 加一条 i → j 的有向边
                if dist <= r2:  # 反向判断 j 的爆炸范围是否覆盖 i
                    g[j].append(i)  # 若是则加一条 j → i 的有向边
        ans = 0  # 记录所有起点中最多能引爆的炸弹数
        for k in range(n):  # 依次以每颗炸弹作为最初引爆点
            vis = {k}  # 用集合记录已被引爆的炸弹，起点先放进去
            q = [k]  # 用列表当 BFS 队列，起点入队
            for i in q:  # 直接在 q 上迭代：循环中 append 的元素也会被遍历到，等价于 BFS
                for j in g[i]:  # 遍历当前炸弹能直接引爆的炸弹
                    if j not in vis:  # 只处理还没被引爆过的，避免重复
                        vis.add(j)  # 标记为已引爆
                        q.append(j)  # 加入队列，等待继续向外连锁扩散
            if len(vis) == n:  # 已经能引爆全部炸弹，不可能更优
                return n  # 提前返回 n
            ans = max(ans, len(vis))  # 用本轮的引爆数更新最大值
        return ans  # 返回所有起点中的最大引爆数
