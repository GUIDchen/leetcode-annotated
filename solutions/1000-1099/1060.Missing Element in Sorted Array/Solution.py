# 题目：1060. 有序数组中的缺失元素（Missing Element in Sorted Array）
# 思路：missing(i) = nums[i] - nums[0] - i 表示前 i 个元素之间缺失的个数，单调不减，于是可二分查找第 k 个缺失值所在区间。
# 时间复杂度：O(log n)，二分查找；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def missingElement(self, nums: List[int], k: int) -> int:  # nums 严格递增，返回第 k 个缺失的正整数
        def missing(i: int) -> int:  # 计算 nums[0..i] 之间缺失的数字个数
            return nums[i] - nums[0] - i  # 数值跨度减去已有元素个数，即为缺失个数

        n = len(nums)  # 数组长度
        if k > missing(n - 1):  # 第 k 个缺失值在数组末尾之后
            return nums[n - 1] + k - missing(n - 1)  # 从最后一个元素直接往后数出答案
        l, r = 0, n - 1  # 二分区间：找第一个 missing(i) >= k 的位置
        while l < r:  # 区间收缩到单点
            mid = (l + r) >> 1  # 取中点，>> 1 等价于整除 2
            if missing(mid) >= k:  # 答案在 mid 或更左侧
                r = mid  # 收缩右边界
            else:  # 答案在 mid 右侧
                l = mid + 1  # 收缩左边界
        return nums[l - 1] + k - missing(l - 1)  # 从 l-1 处的元素继续向后数出答案
