# 题目：851. 喧闹和富有（Loud and Rich）
# 思路：把 richer 看成「更有钱 → 更穷」的有向边，从每个人出发做记忆化 DFS，取子树中 quiet 最小的编号。
# 时间复杂度：O(n + m)，每个点只求解一次；空间复杂度：O(n + m)，邻接表与答案数组。
class Solution:  # 题解类
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:  # richer 给出贫富关系，quiet 越小代表越安静
        def dfs(i: int):  # 求 i 可达范围内 quiet 最小的编号
            if ans[i] != -1:  # 已计算过就直接复用结果
                return  # 提前返回，避免重复搜索
            ans[i] = i  # 先假设答案是自己
            for j in g[i]:  # 遍历所有比 i 有钱的人
                dfs(j)  # 先递归求出 j 的答案
                if quiet[ans[j]] < quiet[ans[i]]:  # 若 j 的答案更安静则更新 i 的答案
                    ans[i] = ans[j]  # 记录更安静的编号

        g = defaultdict(list)  # 邻接表：g[b] 存放比 b 更有钱的人
        for a, b in richer:  # 遍历贫富关系 a 比 b 有钱
            g[b].append(a)  # 建边 b → a
        n = len(quiet)  # 人数
        ans = [-1] * n  # 记忆化数组，-1 表示尚未计算
        for i in range(n):  # 对每个人都求一次答案
            dfs(i)  # 记忆化 DFS
        return ans  # 返回每个人的答案
