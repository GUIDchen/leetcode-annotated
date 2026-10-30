# 题目：575. 分糖果（Distribute Candies）
# 核心思路：妹妹最多拿一半（n/2）颗，能尝到的种类数不超过糖果总种类数，答案是两者较小值。
# 时间复杂度：O(n)，去重需要一次遍历；空间复杂度：O(n)，集合最多存 n 个不同种类。
class Solution:  # LeetCode 约定的题解类
    def distributeCandies(self, candyType: List[int]) -> int:  # candyType 是各颗糖果的类型编号
        return min(len(candyType) >> 1, len(set(candyType)))  # 右移一位等于除以 2：在「能拿的颗数」与「种类数」中取较小值
