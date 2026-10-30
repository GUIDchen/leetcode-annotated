# 题目：2602. 使数组元素全部相等的最少操作次数（Minimum Operations to Make All Array Elements Equal）
# 思路：排序 + 前缀和；对每个查询 x 二分出小于 x 与大于 x 的分界，用前缀和 O(1) 算出两侧的调整量。
# 时间复杂度：O(n log n + q log n)；空间复杂度：O(n)，前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], queries: List[int]) -> List[int]:  # nums：待统一数组；queries：每次的目标值；返回每个查询的最少操作次数
        nums.sort()  # 先排序，才能用前缀和 + 二分把单个查询降到 O(log n)
        s = list(accumulate(nums, initial=0))  # 前缀和，initial=0 让 s[0]=0，方便用 s[i] 直接表示前 i 项和
        ans = []  # 收集每个查询的答案
        for x in queries:  # 逐个处理查询目标值 x
            i = bisect_left(nums, x + 1)  # 第一个大于 x 的位置：从它到末尾的元素都要减到 x
            t = s[-1] - s[i] - (len(nums) - i) * x  # 大于 x 的部分：后半段原和减去它们降到 x 后的总和
            i = bisect_left(nums, x)  # 第一个大于等于 x 的位置：它之前的元素都要增到 x
            t += x * i - s[i]  # 小于 x 的部分：这 i 个元素升到 x 后的和减去原和
            ans.append(t)  # 两部分相加即为该查询的答案
        return ans  # 返回全部查询的答案
