# 题目：2833. 距离原点最远的点（Furthest Point From Origin）
# 思路：分别统计 'L'、'R'、'_' 的数量。'L' 与 'R' 决定无法更改的净位移，而每个 '_' 都能任选方向，让它们全部朝净位移的方向走即可使距离最大，故答案为 |L 数 - R 数| + '_' 数。
# 时间复杂度：O(n)，对字符串做了常数次遍历；空间复杂度：O(1)，只用常数个临时值。
class Solution:  # LeetCode 约定的题解类
    def furthestDistanceFromOrigin(self, moves: str) -> int:  # moves：由 'L'、'R'、'_' 组成的移动序列
        return abs(moves.count("L") - moves.count("R")) + moves.count("_")  # 固定位移的绝对值加上所有 '_' 同向移动带来的最大额外距离
