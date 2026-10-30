# 3969. Valid Subarrays With Matching Sum Digits I | 求和后首尾数字相同的有效子数组 I（中等）
# 核心思路：n 很小，直接枚举所有子数组，边累加区间和边判断：区间和末位等于 x 用 s % 10 判断，首位则把和转成字符串取第 0 个字符再转成整数比较。
# 复杂度：时间 O(n^2 · log S)，S 为区间和的量级（每对 (l, r) 一次求和与一次 str 转换）；空间 O(1)，只用常数个变量。
class Solution:  # 定义题解类
    def countValidSubarrays(self, nums: list[int], x: int) -> int:  # 返回“区间和首位与末位都等于 x”的子数组个数
        n = len(nums)  # 数组长度
        ans = 0  # 符合条件的子数组计数
        for l in range(n):  # 枚举子数组左端点 l
            s = 0  # 以 l 为起点的区间和
            for r in range(l, n):  # 枚举右端点 r，区间即 nums[l..r]
                s += nums[r]  # 把 nums[r] 并入当前区间和
                if s % 10 == x and int(str(s)[0]) == x:  # 末位由 s % 10 得到；首位用 str(s)[0] 取最高位字符再转成整数
                    ans += 1  # 首位与末位都等于 x，计数加一
        return ans  # 返回满足条件的子数组总数
