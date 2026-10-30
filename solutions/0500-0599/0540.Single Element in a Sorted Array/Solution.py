# 题目：540. 有序数组中的单一元素（Single Element in a Sorted Array）
# 思路：二分。未出现单一元素之前，成对元素的下标是 (偶数, 奇数)；用 mid^1 找到与 mid 配对的另一个下标，若两者值不相等则单一元素在左半区（含 mid），否则在右半区。
# 时间复杂度：O(log n)，每次折半；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def singleNonDuplicate(self, nums: List[int]) -> int:  # nums 是有序数组；返回只出现一次的那个数
        l, r = 0, len(nums) - 1  # 二分区间 [l, r]，初始覆盖整个数组
        while l < r:  # 区间未收缩到单个元素时继续二分
            mid = (l + r) >> 1  # 取中点；右移一位等价于整除 2
            if nums[mid] != nums[mid ^ 1]:  # mid^1 在 mid 为偶数时得到 mid+1、为奇数时得到 mid-1，即它的配对下标
                r = mid  # 配对位置的值不相等，说明单一元素不在 mid 右边，收缩右边界到 mid
            else:  # 否则（分支引入）说明 mid 之前都成对，单一元素在 mid 右边
                l = mid + 1  # 左边界跳到 mid+1，继续在右半区二分
        return nums[l]  # l==r 时区间只剩一个元素，它就是单一元素
