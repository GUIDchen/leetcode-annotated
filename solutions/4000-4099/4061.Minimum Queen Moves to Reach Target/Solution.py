# 题目：4061. 皇后到达目标格子的最少移动步数（Minimum Queen Moves to Reach Target）
# 思路：皇后一步可以横走、竖走或沿对角线走任意距离，因此起点等于终点时是 0 步；二者同行、同列或同一对角线（行列差绝对值相等）时可以一步直达；其余情况先走到与起点同行（或同列）且与终点同对角线的格子，再一步进终点，至多 2 步，所以答案只可能是 0、1、2。
# 时间复杂度：O(1)，只做常数次比较与取绝对值；空间复杂度：O(1)，只用到几个整数变量。
class Solution:  # LeetCode 约定的题解类
    def minQueenMoves(self, source: list[int], target: list[int]) -> int:  # source、target 为起点与终点的 [行, 列]；返回皇后最少移动步数
        sr, sc = source  # 拆出起点行列
        tr, tc = target  # 拆出终点行列
        if sr == tr and sc == tc:  # 起点就是终点
            return 0  # 已经在目标格子，0 步
        if sr == tr or sc == tc or abs(sr - tr) == abs(sc - tc):  # 同行、同列或同一对角线（行列差绝对值相等），皇后一步可达
            return 1  # 一步直达
        return 2  # 其余位置先横竖走到与终点同对角线的格子，再斜走一步，两步必达
