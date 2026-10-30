# 题目：1431. 拥有最多糖果的孩子（Kids With the Greatest Number of Candies）
# 思路：先求原有糖果数的最大值，再用列表推导逐个判断加上额外糖果后能否达到它。
# 时间复杂度：O(n)，两遍扫描；空间复杂度：O(n)，存放返回的 bool 列表。
class Solution:  # LeetCode 约定的题解类
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:  # candies：每个孩子已有的糖果数；extraCandies：可额外给的糖果数
        mx = max(candies)  # 第一遍扫描：求所有孩子糖果数的最大值
        return [candy + extraCandies >= mx for candy in candies]  # 第二遍扫描并直接构造结果：加上额外糖果后不小于原最大值即为 True
