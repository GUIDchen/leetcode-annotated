# 题目：1121. 将数组分成几个递增序列（Divide Array Into Increasing Sequences）
# 思路：数组非降序，同一值重复 cnt 次就必须分进 cnt 个不同子序列，因此至少需要 cnt*k 个元素；用 groupby 求最大重复次数即可。
# 时间复杂度：O(n)，groupby 只需一遍扫描；空间复杂度：O(1)，只保存当前最大组长度。
class Solution:  # LeetCode 约定的题解类
    def canDivideIntoSubsequences(self, nums: List[int], k: int) -> bool:  # 判断能否切成若干不相交的、长度至少为 k 的严格递增子序列
        mx = max(len(list(x)) for _, x in groupby(nums))  # groupby 按值把相邻相同元素分组，list(x) 的长度就是该值的重复次数，取其中最大值
        return mx * k <= len(nums)  # 每个重复值都要占一个独立子序列，元素总数够才有解
