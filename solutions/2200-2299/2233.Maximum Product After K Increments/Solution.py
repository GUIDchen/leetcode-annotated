# 题目：2233. K 次增加后的最大乘积（Maximum Product After K Increments）
# 核心思路：贪心——每次把 1 加到当前最小值上，总乘积增长最多；
#           用最小堆反复替换堆顶，最后累乘全部元素并取模。
# 时间复杂度：O(n + k log n)；空间复杂度：O(1)（原地把 nums 调整为堆，不计输入本身占用）。
class Solution:  # LeetCode 约定的题解类
    def maximumProduct(self, nums: List[int], k: int) -> int:  # nums：初始数组；k：最多增加的次数
        heapify(nums)  # 原地把 nums 整理成最小堆，nums[0] 成为最小值
        for _ in range(k):  # 重复 k 次「把最小值加一」
            heapreplace(nums, nums[0] + 1)  # 弹出堆顶并把「堆顶 + 1」压回，一步完成且保持堆序
        mod = 10**9 + 7  # 题目要求的取模常量
        return reduce(lambda x, y: x * y % mod, nums)  # 从左到右累乘，每步取模避免大整数
