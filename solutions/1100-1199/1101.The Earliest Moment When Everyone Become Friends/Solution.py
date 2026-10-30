# 题目：1101. 彼此熟识的最早时间（The Earliest Moment When Everyone Become Friends）
# 思路：按时间升序处理日志，用并查集合并朋友关系，连通分量数减到 1 时返回该条日志的时间。
# 时间复杂度：O(m log m + m α(n))，瓶颈在排序；空间复杂度：O(n)，并查集数组。
class Solution:  # LeetCode 约定的题解类
    def earliestAcq(self, logs: List[List[int]], n: int) -> int:  # logs 每项是 [时间, 人x, 人y]，n 是总人数
        def find(x):  # 带路径压缩的查找函数
            if p[x] != x:  # 还不是根就继续往上找
                p[x] = find(p[x])  # 递归找到根后回填，压缩路径
            return p[x]  # 返回根节点

        p = list(range(n))  # 并查集初始化：每人一个集合
        for t, x, y in sorted(logs):  # 按时间升序处理，sorted 会先按首元素（时间）比较
            if find(x) == find(y):  # 两人已经在同一集合，这条关系没有新信息
                continue  # 跳过，处理下一条日志
            p[find(x)] = find(y)  # 合并两个集合：把 x 的根挂到 y 的根下面
            n -= 1  # 连通分量个数减一（n 在此复用为分量计数）
            if n == 1:  # 只剩一个连通分量，所有人都互相认识
                return t  # 返回当前这条日志的时间，即最早时刻
        return -1  # 日志处理完仍未全员连通，返回 -1
