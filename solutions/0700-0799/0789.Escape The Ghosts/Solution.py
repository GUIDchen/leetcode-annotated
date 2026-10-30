# 题目：789. 逃脱阻碍者（Escape The Ghosts）
# 思路：起点 (0,0) 到 target 的曼哈顿距离是固定下界；任何阻碍者距离不超过它就能提前拦截，反之我一定可以逃脱。
# 时间复杂度：O(g)，g 是阻碍者数量；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def escapeGhosts(self, ghosts: List[List[int]], target: List[int]) -> bool:  # ghosts 是阻碍者坐标，target 是目的地，返回能否安全到达
        tx, ty = target  # 拆出目的地的横纵坐标
        return all(abs(tx - x) + abs(ty - y) > abs(tx) + abs(ty) for x, y in ghosts)  # 生成器表达式逐个比较：所有阻碍者都比起点更远才可能逃脱（all 遇到第一个不满足即返回 False）
