# 题目：896. 单调数列（Monotonic Array）
# 核心思路：用 pairwise 生成相邻元素对，分别判断是否全部非递减、全部非递增，满足其一即单调。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，pairwise 为惰性生成。
class Solution:  # LeetCode 约定的题解类
    def isMonotonic(self, nums: List[int]) -> bool:  # nums：待判定的数组
        asc = all(a <= b for a, b in pairwise(nums))  # 全部 a <= b 说明是非递减数列
        desc = all(a >= b for a, b in pairwise(nums))  # 全部 a >= b 说明是非递增数列
        return asc or desc  # 只要满足其中之一就是单调数列
