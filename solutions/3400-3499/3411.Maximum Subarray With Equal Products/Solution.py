# 3411. 最长乘积等价子数组 / Maximum Subarray With Equal Products
# 核心思路：枚举子数组，用乘积 == gcd * lcm 判定等价，并以全局 lcm*max 作为乘积上界提前剪枝。
# 复杂度：时间复杂度 O(n^2 log V)，空间复杂度 O(1)，V 为元素最大值。
class Solution:  # 题解类定义
    def maxLength(self, nums: List[int]) -> int:  # 求满足乘积等于 gcd*lcm 的最长子数组长度
        n = len(nums)  # 数组长度
        ans = 0  # 答案
        max_p = lcm(*nums) * max(nums)  # 乘积上界：全局最小公倍数乘全局最大值
        for i in range(n):  # 枚举左端点
            p, g, l = 1, 0, 1  # p 为乘积，g 为 gcd，l 为 lcm
            for j in range(i, n):  # 枚举右端点
                p *= nums[j]  # 累乘
                g = gcd(g, nums[j])  # 更新最大公约数
                l = lcm(l, nums[j])  # 更新最小公倍数
                if p == g * l:  # 满足乘积等于 gcd*lcm
                    ans = max(ans, j - i + 1)  # 更新最长长度
                if p > max_p:  # 乘积超过上界
                    break  # 提前退出内层循环
        return ans  # 返回最长长度
