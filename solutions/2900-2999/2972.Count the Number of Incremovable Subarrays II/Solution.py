# 题目：2972. 统计移除递增子数组的数目 II（Count the Number of Incremovable Subarrays II）
# 思路：先求最长严格递增前缀末尾 i，再从右往左枚举保留后缀起点 j，双指针累计合法方案（Python 整数无溢出）。
# 时间复杂度：O(n)，两个指针各自单调；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def incremovableSubarrayCount(self, nums: List[int]) -> int:  # nums：输入数组，返回可移除的递增子数组数目
        i, n = 0, len(nums)  # i 为最长严格递增前缀的末尾，n 为数组长度
        while i + 1 < n and nums[i] < nums[i + 1]:  # 前缀能保持严格递增就继续延伸
            i += 1  # 前缀末尾右移
        if i == n - 1:  # 整个数组本来就严格递增
            return n * (n + 1) // 2  # 任意子数组都可移除，答案是全部子数组个数
        ans = i + 2  # 先计入删到末尾的方案：左端点 0..i+1 共 i+2 种
        j = n - 1  # j 从最右端开始，作为保留后缀的起点
        while j:  # j 减到 0 时后缀为空，循环结束
            while i >= 0 and nums[i] >= nums[j]:  # 左端点不能超过 i，且必须让 nums[i] < nums[j]
                i -= 1  # 左移前缀末尾直到满足递增
            ans += i + 2  # 左端点可取 0..i+1，共 i+2 种
            if nums[j - 1] >= nums[j]:  # 后缀自身不严格递增，更长的后缀也不合法
                break  # 提前退出
            j -= 1  # j 左移，扩大保留的后缀
        return ans  # 返回方案总数
