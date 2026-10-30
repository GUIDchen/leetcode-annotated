# 题目：1760. 袋子里最少数目的球（Minimum Limit of Balls in a Bag）
# 思路：二分答案。上限 mx 越小需要操作越多，具有单调性；把 x 个球拆到每袋不超过 mx 需 (x-1)//mx 次操作。
# 时间复杂度：O(n log M)，M = max(nums)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumSize(self, nums: List[int], maxOperations: int) -> int:  # nums：每袋球数；maxOperations：最多操作次数
        def check(mx: int) -> bool:  # 判断上限 mx 是否可行（所需操作数不超过限制）
            return sum((x - 1) // mx for x in nums) <= maxOperations  # (x-1)//mx 即 ceil(x/mx)-1，也就是拆分刀数

        return bisect_left(range(1, max(nums) + 1), True, key=check) + 1  # 在候选上限上二分找第一个可行值；range 从 1 开始，故下标加 1 还原取值
