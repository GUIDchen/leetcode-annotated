# 题目：2592. 最大化数组的伟大值（Maximize Greatness of an Array）
# 思路：排序后用双指针贪心匹配：把当前元素当作「更大的那个」，只要它严格大于尚未配对的最小元素 nums[i] 就配成一对并右移 i。
# 时间复杂度：O(n log n)，主要是排序开销；空间复杂度：O(log n)，排序所需的额外空间。
class Solution:  # LeetCode 约定的题解类
    def maximizeGreatness(self, nums: List[int]) -> int:  # nums 是待重排的输入数组
        nums.sort()  # 原地升序排序，使大小关系可以直接用下标比较
        i = 0  # i 是「尚未被配对的最小元素」的下标，同时也等于已经配对成功的数量
        for x in nums:  # 把数组中的元素依次当作配对中「更大的那个」
            i += x > nums[i]  # 布尔值参与加法：x 严格大于 nums[i] 时配对成功，i 右移一位
        return i  # i 的最终值就是最大的伟大值
