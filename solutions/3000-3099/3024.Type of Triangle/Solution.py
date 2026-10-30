# 题目：3024. 三角形类型（Type of Triangle）
# 核心思路：先对三边排序，用最短两边之和 > 最长边判断能否成三角形；再依次比较三边是否全相等（等边）、是否有两边相等（等腰），否则为不等边。
# 时间复杂度：O(1)（只有 3 个元素排序）；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def triangleType(self, nums: List[int]) -> str:  # nums：长度为 3 的边长列表，返回三角形类型字符串
        nums.sort()  # 原地排序，使 nums[0] ≤ nums[1] ≤ nums[2]
        if nums[0] + nums[1] <= nums[2]:  # 两条短边之和不超过最长边，三边构不成三角形
            return "none"  # 按题意返回 "none"
        if nums[0] == nums[2]:  # 最短边等于最长边，说明三条边全都相等
            return "equilateral"  # 三边相等，等边三角形
        if nums[0] == nums[1] or nums[1] == nums[2]:  # 存在两条边相等（此时已排除三边全等）
            return "isosceles"  # 两条边相等，等腰三角形
        return "scalene"  # 三边互不相等，返回不等边三角形
