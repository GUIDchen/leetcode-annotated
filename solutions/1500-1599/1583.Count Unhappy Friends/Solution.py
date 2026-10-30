# 题目：1583. 统计不开心的朋友（Count Unhappy Friends）
# 思路：用字典表记录每人的亲密度排名，再对每个人检查“比他现任更亲密的人”是否也更喜欢他，是则计为不开心。
# 时间复杂度：O(n^2)，建表与枚举排名都是平方级；空间复杂度：O(n^2)，保存排名表。
class Solution:  # LeetCode 约定的题解类
    def unhappyFriends(  # 参数跨行书写，含义见下面两行注释
        self, n: int, preferences: List[List[int]], pairs: List[List[int]]
    ) -> int:  # self 为实例，n 为人数，preferences 为亲密排序，pairs 为配对结果
        d = [{x: j for j, x in enumerate(p)} for p in preferences]  # d[i][x] 表示 x 在 i 心中的排名，越小越亲密
        p = {}  # p[x] 记录 x 当前的配对伙伴
        for x, y in pairs:  # 遍历所有配对
            p[x] = y  # 双向登记伙伴关系
            p[y] = x  # 保证从任意一方都能查到对方
        ans = 0  # 不开心的人数
        for x in range(n):  # 逐个人判断是否不开心
            y = p[x]  # x 的现任伙伴
            for i in range(d[x][y]):  # 只枚举排名比现任 y 更靠前的人
                u = preferences[x][i]  # 比 y 更亲密的候选 u
                v = p[u]  # u 的现任伙伴 v
                if d[u][x] < d[u][v]:  # u 也觉得 x 比 v 更亲密，即互相更喜欢
                    ans += 1  # 记 x 为不开心的朋友
                    break  # 同一个人只统计一次，跳出内层循环
        return ans  # 返回不开心的朋友总数
