# 题目：154. 寻找旋转排序数组中的最小值 II（Find Minimum in Rotated Sorted Array II）
# 思路：二分。比较 nums[mid] 与 nums[r]：大于则答案在右半段，小于则答案在 [l, mid]，等值无法区分时让 r 减一丢掉一个重复元素。
# 时间复杂度：平均 O(log n)，最坏 O(n)（元素全相等时逐个收缩）；空间复杂度：O(1)，只用了 l、r、mid 三个变量。
class Solution:  # LeetCode 约定的题解类
    def findMin(self, nums: List[int]) -> int:  # nums 是旋转后可能含重复元素的升序数组，返回其中的最小值
        l, r = 0, len(nums) - 1  # 闭区间 [l, r] 表示当前答案可能存在的范围
        while l < r:  # 区间只剩一个元素时该元素即最小值，故以 l < r 为继续搜索的条件
            mid = (l + r) >> 1  # 取中点；(l + r) >> 1 等价于向下取整地除以 2
            if nums[mid] > nums[r]:  # 中点值大于右端值：mid 右侧出现过下降，最小值一定在那一边
                l = mid + 1  # 丢弃左半段（含 mid），下界推到 mid + 1
            elif nums[mid] == nums[r]:  # 中点值等于右端值：无法判断答案方位，但 r 处元素有 mid 处的等值元素可替代
                r -= 1  # 丢掉一个重复元素，安全地缩小范围
            else:  # 中点值小于右端值：[mid, r] 升序，最小值不会在 mid 右侧
                r = mid  # 答案可能是 mid 本身，保留 mid，把上界收缩到 mid
        return nums[l]  # 此时 l == r，返回唯一剩下的元素即最小值
