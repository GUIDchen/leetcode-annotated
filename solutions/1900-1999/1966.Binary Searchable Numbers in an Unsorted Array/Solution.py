# 题目：1966. 未排序数组中的可被二分查找的数（Binary Searchable Numbers in an Unsorted Array）
# 思路：某元素能被二分查到，当且仅当它不小于左侧所有元素、不大于右侧所有元素；先从左扫查前缀最大，再从右扫查后缀最小。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(n)，ok 列表记录每个位置是否仍是候选。
class Solution:  # LeetCode 约定的题解类
    def binarySearchableNumbers(self, nums: List[int]) -> int:  # nums 是待判断的数组，返回可被二分查找命中的元素个数
        n = len(nums)  # 数组长度
        ok = [1] * n  # ok[i] 为 1 表示下标 i 仍是候选，被置 0 即排除
        mx, mi = -1000000, 1000000  # mx 是左侧最大值，mi 是右侧最小值，用值域（1..10^6）之外的哨兵初始化
        for i, x in enumerate(nums):  # 从左到右扫描，同时取得下标 i 与元素 x
            if x < mx:  # 左边存在比它大的数，二分时可能走错方向
                ok[i] = 0  # 标记为不合格
            else:  # 否则它不小于左侧所有元素
                mx = x  # 更新左侧最大值（只需在合格时才可能变大）
        for i in range(n - 1, -1, -1):  # 从右到左扫描，检查「不大于右侧所有元素」
            if nums[i] > mi:  # 右边存在比它小的数
                ok[i] = 0  # 标记为不合格
            else:  # 否则它不大于右侧所有元素
                mi = nums[i]  # 更新右侧最小值（同样只在合格时更新）
        return sum(ok)  # sum 把仍为 1 的位置计数，即答案
