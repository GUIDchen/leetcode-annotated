# 题目：2970. 统计移除递增子数组的数目 I（Count the Number of Incremovable Subarrays I）
# 思路：求出最长严格递增前缀末尾 i，从右往左枚举保留后缀起点 j，双指针累计合法左右端点数。
# 时间复杂度：O(n)，i 单调递减、j 单调递减；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def incremovableSubarrayCount(self, nums: List[int]) -> int:  # nums：输入数组，返回可移除的递增子数组数目
        i, n = 0, len(nums)  # i 为最长严格递增前缀的末尾下标，n 为数组长度
        while i + 1 < n and nums[i] < nums[i + 1]:  # 后一个严格大于前一个时，前缀继续延伸
            i += 1  # 前缀右移一位
        if i == n - 1:  # 整个数组本来就严格递增
            return n * (n + 1) // 2  # 删掉任意子数组后仍递增，答案是全部子数组个数 n*(n+1)//2
        ans = i + 2  # 先计入删到数组末尾的情形：左端点可取 0..i+1，共 i+2 种
        j = n - 1  # j 从最右端开始作为保留的后缀起点
        while j:  # j 为 0 时后缀为空，循环自然结束
            while i >= 0 and nums[i] >= nums[j]:  # 左端点不能超过 i，且要让前缀末尾小于 nums[j] 才保持递增
                i -= 1  # 不断左移前缀末尾
            ans += i + 2  # 左端点 l 可取 0..i+1，共 i+2 种删法
            if nums[j - 1] >= nums[j]:  # 保留的后缀自身不再严格递增，则更长方案也不合法
                break  # 提前退出
            j -= 1  # j 左移，扩大保留的后缀
        return ans  # 返回累计的方案数
