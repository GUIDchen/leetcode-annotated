# 题目：713. 乘积小于 K 的子数组（Subarray Product Less Than K）
# 核心思路：滑动窗口。窗口乘积 p 始终维护为 [l, r] 内元素之积；p 一旦大于等于 k 就右移 l 缩小窗口，此时以 r 结尾的合法子数组恰有 r - l + 1 个。
# 时间复杂度：O(n)，每个元素最多进入、离开窗口各一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:  # nums 是正整数数组，返回乘积严格小于 k 的连续子数组个数
        ans = l = 0  # 链式赋值把 ans 与 l 都初始化为 0；l 是滑动窗口的左端点
        p = 1  # p 维护窗口 [l, r] 内所有元素的乘积
        for r, x in enumerate(nums):  # 同时取出右端点 r 与元素值 x，逐步扩张窗口
            p *= x  # 把新元素乘进窗口乘积
            while l <= r and p >= k:  # 乘积过大时不断右移左端点，直到乘积重新小于 k
                p //= nums[l]  # 用整除把左端点元素从乘积中除掉
                l += 1  # 左端点右移一位，窗口收缩
            ans += r - l + 1  # 此时以 r 结尾、长度从 1 到 r - l + 1 的子数组都满足条件，一次性全部累加
        return ans  # 返回满足条件的子数组总数
