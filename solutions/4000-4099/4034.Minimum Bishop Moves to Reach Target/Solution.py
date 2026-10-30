# 题目：4034. 象到达目标格子的最少移动步数 / Minimum Bishop Moves to Reach Target
# 核心思路：象每一步都保持所在格子的颜色不变，先用行列和的奇偶判断可达性，再看两点是否共对角线决定用 1 步还是 2 步
# 复杂度：时间复杂度 O(1)，空间复杂度 O(1)
class Solution:  # 定义 LeetCode 题解类
    def minBishopMoves(self, source: List[int], target: List[int]) -> int:  # 返回象从 source 到 target 的最少移动步数
        sr, sc = source  # 解包起点的行、列坐标
        tr, tc = target  # 解包终点的行、列坐标
        if (sr + sc) % 2 != (tr + tc) % 2:  # 象始终停留在同色格子上，行列和奇偶不同即不可达
            return -1  # 不可达时返回 -1
        if abs(sr - tr) == abs(sc - tc):  # 行列距离相等说明两点在同一条对角线上
            return 1  # 一次移动即可到达
        return 2  # 其余可达情况两次移动即可到达
