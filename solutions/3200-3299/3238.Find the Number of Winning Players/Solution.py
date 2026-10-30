# 题目：3238. 求出胜利玩家的数目（Find the Number of Winning Players）
# 思路：用二维表统计每个玩家拿到每种颜色的次数，次数一旦严格大于玩家编号，就把该玩家放入胜利集合去重。
# 时间复杂度：O(k)，k 为 pick 的长度；空间复杂度：O(n × 11)，计数表的规模。
class Solution:  # LeetCode 约定的题解类
    def winningPlayerCount(self, n: int, pick: List[List[int]]) -> int:  # n 是玩家个数，pick 是 [玩家编号, 颜色] 的记录列表
        cnt = [[0] * 11 for _ in range(n)]  # cnt[x][y] 记录玩家 x 拿到颜色 y 的次数；颜色最多 10，故内层开 11 列
        s = set()  # 胜利玩家编号集合，自动去重
        for x, y in pick:  # 逐条遍历捡球记录，x 是玩家编号、y 是颜色
            cnt[x][y] += 1  # 该玩家该颜色的计数加一
            if cnt[x][y] > x:  # 数量严格大于玩家编号就获胜
                s.add(x)  # 记入胜利集合
        return len(s)  # 返回胜利玩家个数
