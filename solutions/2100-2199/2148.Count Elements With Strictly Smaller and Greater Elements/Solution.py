# 题目：2148. 元素计数（Count Elements With Strictly Smaller and Greater Elements）
# 思路：先求出数组的最小值与最大值，再统计严格介于两者之间的元素个数。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用了两个变量。
class Solution:  # LeetCode 约定的题解类
    def countElements(self, nums: List[int]) -> int:  # nums：输入的整数数组
        mi, mx = min(nums), max(nums)  # 数组中的最小值与最大值
        return sum(mi < x < mx for x in nums)  # 生成器里每个布尔值当 0/1 相加，即严格介于两者之间的元素个数
