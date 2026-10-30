# 4063. 至多一次取反能被 K 整除的最长子数组 I  Longest Subarray Divisible by K with At Most One Negation I
# 核心思路：枚举被取反的下标（含不取反的情况），用前缀和余数首次出现的位置求最长可整除子数组。
# 复杂度：时间 O(n^2)，空间 O(k)。

class Solution:
    def longestSubarray(self, nums: list[int], k: int) -> int:  # 返回至多取反一个元素后，和能被 k 整除的最长子数组长度
        def f(nums: list[int], k: int) -> int:  # 辅助函数：求当前数组中和能被 k 整除的最长子数组长度
            d = {0: -1}  # 余数 -> 首次出现下标，空前缀余数为 0、虚拟下标为 -1
            s = res = 0  # s 为当前前缀和余数，res 为最长长度
            for i, x in enumerate(nums):  # 依次枚举每个元素
                s = (s + x) % k  # 更新前缀和余数（Python 取模结果非负）
                if s in d:  # 该余数此前出现过
                    res = max(res, i - d[s])  # 用当前下标减去最早下标更新答案
                else:  # 该余数首次出现
                    d[s] = i  # 记录其最早下标
            return res  # 返回本轮的最长长度

        ans = f(nums, k)  # 完全不取反时的答案
        for i, x in enumerate(nums):  # 枚举每一个被取反的位置
            nums[i] = -x  # 将第 i 个元素就地取反
            ans = max(ans, f(nums, k))  # 取反后重新计算并更新答案
            nums[i] = x  # 恢复原值，以便枚举下一个位置
        return ans  # 返回最终最大长度
