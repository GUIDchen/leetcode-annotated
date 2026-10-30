# 题目：2447. 最大公因数等于 K 的子数组数目（Number of Subarrays With GCD Equal to K）
# 思路：枚举左端点 i，切片 nums[i:] 再按顺序逐个纳入右端点，一边延伸一边用 gcd 增量维护当前子数组的最大公因数，等于 k 就计数。
# 时间复杂度：O(n^2 log V)，共 O(n^2) 次 gcd 运算，每次 O(log V)；空间复杂度：O(n)，切片 nums[i:] 会复制一段后缀。
class Solution:  # LeetCode 约定的题解类
    def subarrayGCD(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是目标最大公因数
        ans = 0  # 统计满足条件的子数组个数
        for i in range(len(nums)):  # 枚举子数组左端点 i
            g = 0  # 区间 GCD 初值取 0，因为 gcd(0, x) = x，第一个元素纳入时刚好等于它自己
            for x in nums[i:]:  # 切片取 i 开始的后缀，x 依次充当右端点元素
                g = gcd(g, x)  # 把 x 并入当前子数组，增量维护区间 GCD
                ans += g == k  # 区间 GCD 恰为 k 时计数加一（布尔值参与加法）
        return ans  # 返回满足条件的子数组总数
