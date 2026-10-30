# 题目：3189. 得到一个和平棋盘的最少步骤（Minimum Moves to Get a Peaceful Board）
# 思路：和平棋盘要求所有车占据互不相同的行与列；行坐标排序后依次对齐到 0..n-1，列坐标同理，两部分差值绝对值之和就是答案。
# 时间复杂度：O(n log n)，两次排序；空间复杂度：O(log n)，排序所需的递归栈。
class Solution:  # LeetCode 约定的题解类
    def minMoves(self, rooks: List[List[int]]) -> int:  # rooks 是各车的 (行, 列)，返回使两两不能互攻的最少移动步数
        rooks.sort()  # 按行升序排序，行方向可以独立求最优
        ans = sum(abs(x - i) for i, (x, _) in enumerate(rooks))  # 第 i 辆车对齐到第 i 行，差值绝对值之和就是行方向的最小代价
        rooks.sort(key=lambda x: x[1])  # 再按列排序，独立求解列方向
        ans += sum(abs(y - j) for j, (_, y) in enumerate(rooks))  # 第 j 辆车对齐到第 j 列，累加列方向的最小代价
        return ans  # 行、列两步互不影响，总代价即答案
