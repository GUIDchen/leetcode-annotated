# 题目：2543. 判断一个点是否可以到达（Check if Point Is Reachable）
# 思路：操作只影响坐标的最大公约数中 2 的因子，若 gcd 含奇质因子则永远消不掉；gcd 是 2 的幂即可达。
# 时间复杂度：O(log min(targetX, targetY))，只做一次 gcd；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def isReachable(self, targetX: int, targetY: int) -> bool:  # 判断目标点能否从 (1, 1) 变换得到（gcd 由判题环境隐式提供，不补 import）
        x = gcd(targetX, targetY)  # 求两坐标的最大公约数，可达性完全由它决定
        return x & (x - 1) == 0  # 位运算优先级高于比较，等价于 (x & (x - 1)) == 0；为 0 说明 x 是 2 的幂，可达
