# 题目：2576. 求出最多标记下标（Find the Maximum Number of Marked Indices）
# 思路：排序后把数组分成左右两半，用双指针贪心匹配，让右半每个元素尽量配对左半的最小可用元素。
# 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(1)，只用到常数个变量（不计排序开销）。
class Solution:  # LeetCode 约定的题解类
    def maxNumOfMarkedIndices(self, nums: List[int]) -> int:  # nums 是输入数组，返回最多能标记的下标个数
        nums.sort()  # 升序排序，便于用双指针做贪心匹配
        i, n = 0, len(nums)  # i 指向左半部分下一个待配对的位置；n 是数组长度
        for x in nums[(n + 1) // 2 :]:  # 只扫描右半部分，保证同一个下标不会被重复使用
            if nums[i] * 2 <= x:  # 右半元素至少是左半元素的两倍，满足配对条件
                i += 1  # 配对成功，左指针后移一位
        return i * 2  # 每成功配对一组贡献两个下标，因此返回配对数的两倍
