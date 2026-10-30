# 题目：3717. 使数组变美的最小操作次数（Minimum Operations to Make the Array Beautiful）
# 思路：从左到右做 DP，字典记录「上一位置最终取值 -> 已付最小代价」；当前位置只能改成上一取值的不小于 nums[i] 的倍数且不超过 100，滚动更新取最小代价。
# 时间复杂度：O(n·S²)，S = 100 为元素取值上限；空间复杂度：O(S)，字典最多保存 S 个状态。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：目标数组；返回使其变美观（相邻元素成倍数）的最少操作次数
        f = {nums[0]: 0}  # f[上一位置最终取值] = 处理到该位置为止的最小总代价，首元素代价为 0
        for x in nums[1:]:  # 依次处理后面的每一个元素
            g = {}  # g[本位置最终取值] = 最小总代价
            for pre, s in f.items():  # 枚举上一位置的所有取值与对应代价
                cur = (x + pre - 1) // pre * pre  # 不小于 x 的最小 pre 的倍数
                while cur <= 100:  # 枚举所有不超过 100 的 pre 的倍数
                    if cur not in g or g[cur] > s + cur - x:  # 尚未记录或当前方案更优
                        g[cur] = s + cur - x  # 更新最优代价
                    cur += pre  # 试下一个倍数
            f = g  # 滚动到本位置的状态
        return min(f.values())  # 所有末尾取值中取最小总代价
