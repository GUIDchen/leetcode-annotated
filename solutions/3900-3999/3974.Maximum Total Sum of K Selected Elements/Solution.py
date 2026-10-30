# 3974. Maximum Total Sum of K Selected Elements | K 个元素的最大总和（中等）
# 核心思路：要挑 k 个元素并各配一个系数，越大的元素越该配越大的系数，于是先升序排序，再从末尾往前取 k 个元素，第 t 个（从 0 数）配的系数是 max(1, mul - t)，累加即答案。
# 复杂度：时间 O(n log n)，主要是排序；空间 O(n)，排序产生的临时开销可以忽略，答案只用常数变量。
class Solution:  # 定义题解类
    def maxSum(self, nums: list[int], k: int, mul: int) -> int:  # 返回按规则选 k 个元素能得到的最大总和
        nums.sort()  # 原地升序排序，方便从最大值开始贪心
        n = len(nums)  # 数组长度
        ans = 0  # 累加的总和
        for i in range(n - 1, n - 1 - k, -1):  # 从最大的元素开始，倒着取 k 个（下标 n-1 到 n-k）
            ans += nums[i] * max(1, mul)  # 大元素配大系数；mul 已减到 0 或负数时按 1 计，乘积计入总和
            mul -= 1  # 系数减一，留给下一个更小的元素
        return ans  # 返回最大总和
