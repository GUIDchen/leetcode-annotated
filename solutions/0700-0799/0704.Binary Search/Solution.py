# 题目：704. 二分查找（Binary Search）
# 思路：在闭区间 [l, r] 上二分，每次用 nums[mid] 与 target 比较把区间收缩一半，最后只剩一个候选位置再判定。
# 时间复杂度：O(log n)，每轮区间减半；空间复杂度：O(1)，只用了几个下标变量。
class Solution:  # LeetCode 约定的题解类
    def search(self, nums: List[int], target: int) -> int:  # nums 是升序数组，target 是目标值，返回下标或 -1
        l, r = 0, len(nums) - 1  # 闭区间 [l, r]：l 为左端，r 为右端
        while l < r:  # 区间未收缩到单点前继续二分
            mid = (l + r) >> 1  # 取中点，右移一位等价于整除 2
            if nums[mid] >= target:  # 中点值不小于目标，答案在左半边（含 mid）
                r = mid  # 右端点收缩到 mid，保留 mid 作为候选
            else:  # 否则中点值小于目标
                l = mid + 1  # 排除 mid，左端点右移一格
        return l if nums[l] == target else -1  # 只剩一个候选，命中返回下标，否则返回 -1
