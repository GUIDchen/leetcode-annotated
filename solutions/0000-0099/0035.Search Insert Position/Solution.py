# 题目：35. 搜索插入位置（Search Insert Position）
# 思路：在有序数组上做左闭右开的二分，区间收缩到 l == r 时，该位置就是第一个 ≥ target 的下标，即插入位置。
# 时间复杂度：O(log n)，每次折半；空间复杂度：O(1)，只用两个下标变量。
class Solution:  # LeetCode 约定的题解类
    def searchInsert(self, nums: List[int], target: int) -> int:  # nums 是升序数组，target 是待插入值；返回它应该插入的下标
        l, r = 0, len(nums)  # 左闭右开区间 [l, r)：l 从 0 开始，r 取 n 表示越界位置
        while l < r:  # 区间非空就继续折半
            mid = (l + r) >> 1  # 取中点；>> 1 等价于整除 2
            if nums[mid] >= target:  # 中点值 ≥ target，答案只可能在左半边（含 mid）
                r = mid  # 右边界收缩到 mid，保留 mid 作为候选
            else:  # 否则 mid 及左边都 < target，答案在右半边
                l = mid + 1  # 左边界跳到 mid+1，排除掉 mid
        return l  # 循环结束时 l == r，该下标就是插入位置
