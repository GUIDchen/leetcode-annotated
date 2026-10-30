# 题目：319. 灯泡开关（Bulb Switcher）
# 思路：第 i 个灯泡最终是否亮着取决于 i 的约数个数奇偶，只有完全平方数会被切换奇数次。
# 时间复杂度：O(1)，只做一次开方；空间复杂度：O(1)，只用到常数空间。
class Solution:  # LeetCode 约定的题解类
    def bulbSwitch(self, n: int) -> int:  # n 是灯泡总数，返回最终仍然亮着的灯泡个数
        return int(sqrt(n))  # floor(sqrt(n)) 就是 1..n 中完全平方数的个数
