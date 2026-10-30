# 题目：3012. 通过操作使数组长度最小（Minimize Length of Array Using Operations）
# 思路：操作是「删掉 x 和 y，换入 x % y」。取全局最小值 mi：只要有某个数不能被 mi 整除，就能用余数造出比 mi 更小的数，最终把数组削到只剩 1 个；否则所有数都是 mi 的倍数，只能把最小值两两配对消掉，剩 ceil(cnt(mi)/2) 个。
# 时间复杂度：O(n)，两趟线性扫描数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumArrayLength(self, nums: List[int]) -> int:  # nums 是输入数组；返回取模操作后数组可能达到的最小长度
        mi = min(nums)  # mi 是数组最小值：任何取模结果都落在 0..mi-1
        if any(x % mi for x in nums):  # 只要有一个数不能被 mi 整除，就能造出比 mi 更小的数，从而把数组削到只剩 1 个
            return 1  # 长度为 1 已是最小可能，直接返回
        return (nums.count(mi) + 1) // 2  # 所有数都是 mi 的倍数时只能两两消去最小值，个数向上取整（+1 后整除 2）
