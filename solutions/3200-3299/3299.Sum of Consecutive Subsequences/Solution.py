# 题目：3299. 连续子序列的和（Sum of Consecutive Subsequences）🔒
# 思路：按元素贡献计数。正反两遍 DP 统计每个元素出现在多少条「下标递增时数值恰好 +1」的链中，再乘元素值累加。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(n)，left/right 数组与 Counter。
class Solution:  # LeetCode 约定的题解类
    def getSum(self, nums: List[int]) -> int:  # nums：输入数组；返回所有连续子序列元素和之和对 1e9+7 取模的结果
        def calc(nums: List[int]) -> int:  # 内层闭包：统计「数值随下标递增 1」的连续子序列（长度 >= 2）的贡献
            n = len(nums)  # n：数组长度
            left = [0] * n  # left[i]：位置 i 之前能接到 nums[i] 前面的链条数（i 作链尾）
            right = [0] * n  # right[i]：位置 i 之后能接在 nums[i] 后面的链条数（i 作链头）
            cnt = Counter()  # cnt[v]：以值 v 结尾、且数值随下标递增 1 的链条数
            for i in range(1, n):  # 从左往右扫描，递推以每个位置结尾的链条数
                cnt[nums[i - 1]] = (cnt[nums[i - 1]] + 1 + cnt[nums[i - 1] - 1]) % mod  # 所有以 nums[i-1]-1 结尾的链都能接上 nums[i-1]，再加一条只含 nums[i-1] 的新链
                left[i] = cnt[nums[i] - 1]  # 位置 i 左侧能接上的链条数
            cnt = Counter()  # 重置计数器，改用从右往左的扫描
            for i in range(n - 2, -1, -1):  # 从右往左扫描，递推以每个位置开头的链条数
                cnt[nums[i + 1]] = (cnt[nums[i + 1]] + 1 + cnt[nums[i + 1] + 1]) % mod  # 所有以 nums[i+1]+1 开头的链都能前接 nums[i+1]，再加一条只含 nums[i+1] 的新链
                right[i] = cnt[nums[i] + 1]  # 位置 i 右侧能接上的链条数
            return sum((l + r + l * r) * x for l, r, x in zip(left, right, nums)) % mod  # 按乘法原理汇总：i 作链尾、作链头、在中间三种情况，再乘元素值

        mod = 10**9 + 7  # 模数常量 10^9+7
        x = calc(nums)  # x：所有递增（数值随下标 +1）连续子序列的贡献
        nums.reverse()  # 原地反转，原数组的递减链变成递增链
        y = calc(nums)  # y：所有递减（数值随下标 -1）连续子序列的贡献
        return (x + y + sum(nums)) % mod  # 递增 + 递减 + 长度为 1 的子序列（即数组总和）
