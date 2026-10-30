# 3867. 数对的最大公约数之和 / Sum of GCD of Formed Pairs
# 核心思路：先维护前缀最大值 mx，令 prefix_gcd[i] = gcd(nums[i], mx) 得到每个位置可配对的数值；排序后把第 i 小与第 i 大配对，累加各对的 gcd 即为答案。
# 复杂度：时间复杂度 O(n log n)（排序主导），空间复杂度 O(n)。
class Solution:  # LeetCode 题解类
    def gcdSum(self, nums: list[int]) -> int:  # 返回按规则配对后所有数对的 gcd 之和
        n = len(nums)  # 数组长度 n
        prefix_gcd = [0] * n  # 存放每个位置上的前缀 gcd
        mx = 0  # 维护前缀最大值，初值为 0
        for i, x in enumerate(nums):  # 从左到右扫描，构造 prefix_gcd
            mx = max(mx, x)  # 更新到当前位置为止的最大值
            prefix_gcd[i] = gcd(x, mx)  # 当前元素与其前缀最大值的最大公约数
        prefix_gcd.sort()  # 升序排序，为“最小配最大”做准备
        return sum(gcd(prefix_gcd[i], prefix_gcd[-i - 1]) for i in range(n // 2))  # 第 i 小与第 i 大配对，累加每条配对的 gcd
