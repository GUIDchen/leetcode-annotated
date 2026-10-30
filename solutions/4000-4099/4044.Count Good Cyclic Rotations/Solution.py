# 题目：4044. 统计好循环移位的数量（Count Good Cyclic Rotations）
# 思路：环形滑窗求和。先把数组分成长度 m = n//2 的前半与后半并分别求和，之后每右移一位只有两个元素换边（nums[i] 从前半到后半、nums[i+m] 从后半到前半），用 O(1) 增量更新两侧之和，统计「前半之和 > 后半之和」的移位个数。
# 复杂度：时间复杂度 O(n)，n 为数组长度；空间复杂度 O(1)，只用到两侧和与答案等常数变量。
class Solution:  # LeetCode 约定的题解类
    def countGoodRotations(self, nums: list[int]) -> int:  # nums：环形数组；返回「前半之和 > 后半之和」的循环移位个数
        n = len(nums)  # 数组长度，也是循环移位的个数
        m = n // 2  # 前半部分的长度
        l = sum(nums[:m])  # 不移位时前半部分的和
        r = sum(nums[m:])  # 不移位时后半部分的和
        ans = int(l > r)  # 不移位这一种是否满足 l > r
        for i in range(n - 1):  # 依次右移，枚举余下的 n-1 种移位
            l -= nums[i]  # 前半最左的元素被移出前半
            r += nums[i]  # 它进入后半的最右端
            l += nums[(i + m) % n]  # 后半最左的元素换进前半的最右端
            r -= nums[(i + m) % n]  # 同时把它从后半中移除
            ans += int(l > r)  # 当前移位满足 l > r 则累加答案
        return ans  # 返回满足条件的循环移位个数
