# 题目：2098. 长度为 K 的最大偶数和子序列（Subsequence of Size K With the Largest Even Sum）
# 思路：先取最大的 k 个数；若和为奇数，则用「去掉已选最小偶数换入未选最大奇数」或「去掉已选最小奇数换入未选最大偶数」修正奇偶性，取较优者。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，只用了常数个辅助变量。
class Solution:  # LeetCode 约定的题解类
    def largestEvenSum(self, nums: List[int], k: int) -> int:  # nums：候选数组；k：子序列长度；返回最大偶数和，无解时 -1
        nums.sort()  # 升序排序，方便从尾部取最大元素
        ans = sum(nums[-k:])  # 先取最大的 k 个数求和
        if ans % 2 == 0:  # 和已经是偶数
            return ans  # 直接就是最优解
        n = len(nums)  # 数组长度
        mx1 = mx2 = -inf  # 未选部分的：最大奇数 mx1、最大偶数 mx2
        for x in nums[: n - k]:  # 遍历没被选中的较小部分（升序遍历）
            if x & 1:  # 是奇数
                mx1 = x  # 越往后越大，最终得到最大奇数
            else:  # 是偶数
                mx2 = x  # 同理得到最大偶数
        mi1 = mi2 = inf  # 已选部分的：最小偶数 mi1、最小奇数 mi2
        for x in nums[-k:][::-1]:  # 把被选中的 k 个数倒序，即从大到小遍历
            if x & 1:  # 是奇数
                mi2 = x  # 越往后越小，最终得到最小奇数
            else:  # 是偶数
                mi1 = x  # 同理得到最小偶数
        ans = max(ans - mi1 + mx1, ans - mi2 + mx2, -1)  # 两种修正方案取较大者，同时兜底不小于 -1
        return -1 if ans < 0 else ans  # 负数说明无可行方案，返回 -1，否则返回该和
