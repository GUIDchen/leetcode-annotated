# 题目：2009. 使数组连续的最少操作数（Minimum Number of Operations to Make Array Continuous）
# 思路：排序并去重后，枚举每个值作为最终连续区间的左端点，用二分求出落在 [v, v + n - 1] 里的不同元素个数；这些元素可原地保留，其余 n - k 个必须修改，取最小值。
# 时间复杂度：O(n log n)，排序加每个元素一次二分；空间复杂度：O(n)，去重后的新列表。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums 是输入数组；返回把它变成 n 个连续整数所需的最少操作次数
        ans = n = len(nums)  # n 是原数组长度（连续区间必须覆盖 n 个整数），ans 先初始化为最坏情况 n
        nums = sorted(set(nums))  # 排序并去重：只有互不相同的值才可能原地保留
        for i, v in enumerate(nums):  # 枚举每个值作为最终连续区间的左端点
            j = bisect_right(nums, v + n - 1)  # 二分找第一个大于 v + n - 1 的位置 j，[i, j) 内的值都能落在区间里
            ans = min(ans, n - (j - i))  # 区间内的 j - i 个值可保留，其余 n - (j - i) 个必须修改，取最小值
        return ans  # 返回最少修改次数
