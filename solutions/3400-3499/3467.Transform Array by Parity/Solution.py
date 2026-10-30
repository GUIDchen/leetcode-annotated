# 3467. Transform Array by Parity / 3467. 将数组按照奇偶性转化
# 核心思路：统计偶数个数 even，前 even 个位置填 0、其余位置填 1。
# 复杂度：时间 O(n)，空间 O(1)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def transformArray(self, nums: List[int]) -> List[int]:  # 原地把偶数改成 0、奇数改成 1 后返回
        even = sum(x % 2 == 0 for x in nums)  # 统计偶数个数，即最终 0 的个数
        for i in range(even):  # 前 even 个位置填 0
            nums[i] = 0  # 偶数位置赋 0
        for i in range(even, len(nums)):  # 其余位置填 1
            nums[i] = 1  # 奇数位置赋 1
        return nums  # 返回按奇偶性转化后的数组
