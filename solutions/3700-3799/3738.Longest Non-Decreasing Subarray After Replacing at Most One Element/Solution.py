# 题目：3738. 替换至多一个元素后最长非递减子数组（Longest Non-Decreasing Subarray After Replacing at Most One Element）
# 核心思路：先用 left[i] 表示以 i 结尾的最长非递减段长度、right[i] 表示以 i 开头的最长非递减段长度；再枚举被替换的位置 i，若左右邻居能直接衔接（nums[i-1] <= nums[i+1]）就把左右两段合并，否则只能任选较长的一侧，全程取最大值。
# 复杂度：时间 O(n)，两次线性扫描加一次枚举；空间 O(n)，需要 left 与 right 两个辅助数组。
class Solution:  # LeetCode 约定的题解类
    def longestSubarray(self, nums: List[int]) -> int:  # nums：整数数组；返回替换至多一个元素后最长非递减子数组的长度
        n = len(nums)  # 数组长度
        left = [1] * n  # left[i]：以 i 结尾的最长非递减段长度
        right = [1] * n  # right[i]：以 i 开头的最长非递减段长度
        for i in range(1, n):  # 从左往右预处理 left
            if nums[i] >= nums[i - 1]:  # 相邻元素满足非递减
                left[i] = left[i - 1] + 1  # 可以接在上一段后面，长度加一
        for i in range(n - 2, -1, -1):  # 从右往左预处理 right
            if nums[i] <= nums[i + 1]:  # 相邻元素满足非递减
                right[i] = right[i + 1] + 1  # 可以接在后面那一段的前面，长度加一
        ans = max(left)  # 答案至少是原本最长的一段（也可以选择不替换）
        for i in range(n):  # 枚举被替换（即被新值覆盖）的位置 i
            a = 0 if i - 1 < 0 else left[i - 1]  # 左侧能接上的长度，越界则为 0
            b = 0 if i + 1 >= n else right[i + 1]  # 右侧能接上的长度，越界则为 0
            if i - 1 >= 0 and i + 1 < n and nums[i - 1] > nums[i + 1]:  # 左右邻居都存在但接不上：新值无法同时衔接两侧
                ans = max(ans, a + 1, b + 1)  # 只能保留其中一侧，用新值替换掉较短的一侧
            else:  # 两侧可以接上（或只有一侧存在）
                ans = max(ans, a + b + 1)  # 用一个新值把位置 i 替换掉，左右两段合并成一段
        return ans  # 返回最长非递减子数组的长度
