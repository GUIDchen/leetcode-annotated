# 题目：875. 爱吃香蕉的珂珂（Koko Eating Bananas）
# 核心思路：总耗时随速度单调不增，用 bisect_left 在 [1, max(piles)] 上按 check 的真值二分出第一个可行速度。
# 时间复杂度：O(m log M)，m 为堆数、M 为最大堆的石子数；空间复杂度：O(1)，只做原地求和。
class Solution:  # LeetCode 约定的题解类
    def minEatingSpeed(self, piles: List[int], h: int) -> int:  # piles：每堆香蕉数量；h：守卫回来的时限（小时）
        def check(k: int) -> bool:  # 内部判定函数：速度为 k 时能否在 h 小时内吃完
            return sum((x + k - 1) // k for x in piles) <= h  # 每堆耗时 ceil(x / k)，写成 (x + k - 1) // k；总耗时不大于 h 就可行的

        return 1 + bisect_left(range(1, max(piles) + 1), True, key=check)  # 在候选速度 1..max(piles) 上二分：bisect_left 返回第一个 True 的位置，而区间从 1 开始，所以结果要加 1
