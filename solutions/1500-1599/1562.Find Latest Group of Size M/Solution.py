# 题目：1562. 查找大小为 M 的最新分组（Find Latest Group of Size M）
# 思路：用并查集维护连续 1 的分组，按 arr 顺序把 0 翻成 1 并与左右已翻转位置合并；每次合并前检查被合并分组的长度是否恰为 m，即可记下长度 m 分组存在的最后时刻。
# 时间复杂度：O(n α(n))，并查集近似常数；空间复杂度：O(n)，父指针、分组长度与访问标记。
class Solution:  # LeetCode 约定的题解类
    def findLatestStep(self, arr: List[int], m: int) -> int:  # arr：位置翻转顺序；m：目标分组长度
        def find(x):  # 带路径压缩的查根函数
            if p[x] != x:  # 父节点不是自己就继续向上找
                p[x] = find(p[x])  # 递归找根，并把路径上的点直接挂到根下
            return p[x]  # 返回根节点

        def union(a, b):  # 合并 a、b 所在的两个分组
            pa, pb = find(a), find(b)  # 先取出两个分组的根
            if pa == pb:  # 根相同说明已在同一分组
                return  # 无需合并，直接返回
            p[pa] = pb  # 把 a 的根挂到 b 的根下面
            size[pb] += size[pa]  # 更新合并后的分组长度

        n = len(arr)  # 数组长度，也是位置总数
        if m == n:  # 整个数组都是 1 时分组长度就是 n
            return n  # 第 n 步自然满足，直接返回 n
        vis = [False] * n  # vis[v] 表示位置 v 是否已由 0 翻成 1
        p = list(range(n))  # 并查集父指针初始化：每个位置自成一个根
        size = [1] * n  # 每个分组初始长度为 1
        ans = -1  # 记录最后一次出现长度 m 分组的步数，-1 表示从未出现
        for i, v in enumerate(arr):  # 按顺序执行翻转，i 是当前步数下标
            v -= 1  # 题目位置从 1 开始，转成 0 基下标
            if v and vis[v - 1]:  # 左边相邻位置已经是 1，需要合并
                if size[find(v - 1)] == m:  # 合并前左边分组长度恰为 m，说明它此刻仍存在
                    ans = i  # 记下当前步数
                union(v, v - 1)  # 把左右两个分组合并
            if v < n - 1 and vis[v + 1]:  # 右边相邻位置已经是 1，需要合并
                if size[find(v + 1)] == m:  # 合并前右边分组长度恰为 m
                    ans = i  # 记下当前步数
                union(v, v + 1)  # 把当前位置并入右侧分组
            vis[v] = True  # 当前位置正式变成 1
        return ans  # 返回最后一次步数；从未出现则仍为 -1
