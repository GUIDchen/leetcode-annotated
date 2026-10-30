# 题目：2367. 等差三元组的数目（Number of Arithmetic Triplets）
# 核心思路：用 itertools.combinations 枚举所有下标三元组 (a, b, c)，按值判断两段差是否都等于 diff，再对布尔结果求和。
# 时间复杂度：O(n^3)，组合数即 C(n,3) 个三元组；空间复杂度：O(1)，生成器逐个产出，不额外存列表。
class Solution:  # LeetCode 约定的题解类
    def arithmeticTriplets(self, nums: List[int], diff: int) -> int:  # nums 严格递增；diff 是要求的公差
        return sum(b - a == diff and c - b == diff for a, b, c in combinations(nums, 3))  # combinations 来自 itertools：枚举全部三元组，sum 统计 True 的个数作为答案
