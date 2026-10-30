# 题目：2401. 最长优雅子数组（Longest Nice Subarray）
# 思路：滑动窗口维护两两按位与都为 0 的区间，mask 保存窗口内所有元素的按位或；新元素与 mask 相交时不断右移左端点。
# 时间复杂度：O(n)，每个元素最多进出窗口一次；空间复杂度：O(1)，只用了常数个整型变量。
class Solution:  # LeetCode 约定的题解类
    def longestNiceSubarray(self, nums: List[int]) -> int:  # nums：输入数组，返回最长优雅子数组的长度
        ans = mask = l = 0  # ans 记录答案；mask 是窗口内元素的按位或；l 是窗口左端点
        for r, x in enumerate(nums):  # 枚举右端点 r 与当前元素 x
            while mask & x:  # 当前元素与窗口内某元素有公共的 1 位，窗口不再优雅
                mask ^= nums[l]  # 把左端点元素移出窗口：异或清掉它占用的二进制位
                l += 1  # 左端点右移一格，缩小窗口
            mask |= x  # 当前元素进入窗口，把它的二进制位并入 mask
            ans = max(ans, r - l + 1)  # 用当前窗口长度更新答案
        return ans  # 返回最长优雅子数组的长度
