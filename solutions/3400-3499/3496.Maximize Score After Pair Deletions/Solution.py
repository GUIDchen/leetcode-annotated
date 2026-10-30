# 3496. Maximize Score After Pair Deletions / 3496. 最大化配对删除后的得分
# 核心思路：所有元素都会被删掉，总得分等于元素总和减去必须舍弃的部分；n 为奇数时必有一个元素无法配对，舍弃最小值，n 为偶数时舍弃的一定是某个相邻元素对，取最小相邻和。
# 复杂度：时间 O(n)，空间 O(1)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def maxScore(self, nums: List[int]) -> int:  # nums 为待配对的整数数组，返回可获得的最高得分
        s = sum(nums)  # 所有元素的总和
        if len(nums) & 1:  # 长度为奇数，必然剩下一个元素无法配对
            return s - min(nums)  # 舍弃最小的那个元素即可让得分最高
        return s - min(a + b for a, b in pairwise(nums))  # 长度为偶数，舍弃和最小的相邻对后其余元素可全部配对
