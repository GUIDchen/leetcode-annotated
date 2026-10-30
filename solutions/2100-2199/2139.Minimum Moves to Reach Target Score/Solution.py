# 题目：2139. 得到目标值的最少行动次数（Minimum Moves to Reach Target Score）
# 思路：从 target 逆推回 1，偶数优先折半（用掉一次加倍），奇数或加倍次数用尽时只能减一。
# 时间复杂度：O(log target)，每次至少折半或把奇数变成偶数再折半；空间复杂度：O(log target)，递归栈深度。
class Solution:  # LeetCode 约定的题解类
    def minMoves(self, target: int, maxDoubles: int) -> int:  # target：目标值；maxDoubles：最多可用的加倍次数
        if target == 1:  # 已经到 1，不需要任何行动
            return 0  # 步数为 0
        if maxDoubles == 0:  # 没有加倍次数可用了，只能一步一步加一
            return target - 1  # 从 1 加到 target 需要 target-1 步
        if target % 2 == 0 and maxDoubles:  # 目标为偶数且还有加倍次数（maxDoubles 非 0 即真）
            return 1 + self.minMoves(target >> 1, maxDoubles - 1)  # 用掉一次加倍，问题规模折半（>> 1 即除以 2）
        return 1 + self.minMoves(target - 1, maxDoubles)  # 奇数（或加倍已用完）只能先减一，把它变成偶数后继续逆推
