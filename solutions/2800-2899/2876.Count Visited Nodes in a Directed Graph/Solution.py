# 题目：2876. 有向图访问计数（Count Visited Nodes in a Directed Graph）
# 思路：函数图每个点出度为 1，从未计算的点出发走步并打时间戳，遇到环先算环长，再回填整条路径。
# 时间复杂度：O(n)，每个点只被标记和回填一次；空间复杂度：O(n)，答案数组与时间戳数组。
class Solution:  # LeetCode 约定的题解类
    def countVisitedNodes(self, edges: List[int]) -> List[int]:  # edges[i] 是点 i 指向的下一个点
        n = len(edges)  # 节点个数
        ans = [0] * n  # ans：每点能访问到的点数，0 表示还没算
        vis = [0] * n  # vis：本次模拟走到该点时的步数，0 表示没走过
        for i in range(n):  # 依次以每个点为起点出发
            if not ans[i]:  # 只处理还没算出答案的点
                cnt, j = 0, i  # cnt：本路径新标记的点数；j：当前走到的点
                while not vis[j]:  # 一直走到重复经过（进入环）或碰到已算出答案的点
                    cnt += 1  # 步数先加一
                    vis[j] = cnt  # 给 j 打上第 cnt 步的时间戳
                    j = edges[j]  # 沿出边前进一步
                cycle, total = 0, cnt + ans[j]  # cycle：环长；total：从起点出发能走过的总点数
                if not ans[j]:  # ans 为 0 说明 j 是本路径刚走进环的那个点
                    cycle = cnt - vis[j] + 1  # 环长 = 两次经过同一点的步数差加一
                    total = cnt  # 新环时起点先按整条路径的点数计
                j = i  # 回到起点，准备回填
                while not ans[j]:  # 只回填本路径上还没有答案的点
                    ans[j] = max(total, cycle)  # 环上的点取环长，环外的点取剩余路径长度
                    total -= 1  # 前进一步后剩余点数减一
                    j = edges[j]  # 继续沿出边前进
        return ans  # 返回每个点能访问到的点数
