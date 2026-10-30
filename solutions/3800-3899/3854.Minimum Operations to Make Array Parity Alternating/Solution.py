# 3854. 使数组奇偶交替的最少操作 / Minimum Operations to Make Array Parity Alternating（中等）
# 核心思路：奇偶交替只有两种目标模式，即 (nums[i] - i) 的奇偶全部相同；分别枚举两种模式，不匹配的位置必须加减 1（翻转奇偶），若它恰是全局最值就向区间内部调整以免扩大极差，最后按 [操作数, 极差] 字典序取较小者。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 设计一个算法：用最少操作让数组奇偶交替，并让极差最小
    def makeParityAlternating(self, nums: List[int]) -> List[int]:  # 返回 [最少操作数, 该操作数下能达到的最小极差]
        def f(k: int) -> List[int]:  # 目标模式 k：要求 (x - i) 的奇偶恒等于 k
            cnt = 0  # 需要的操作次数
            a, b = inf, -inf  # 调整后的最小值 a 与最大值 b
            for i, x in enumerate(nums):  # 按下标遍历数组
                if ((x - i) & 1) != k:  # 奇偶不符合目标模式，必须加减 1 翻转一次
                    cnt += 1  # 操作数加一
                    if x == mn:  # 若它恰是全局最小值，加 1 后不会把下界变得更低
                        x += 1  # 最小值加一，既翻转奇偶又把极差压到最小
                    elif x == mx:  # 若它恰是全局最大值，减 1 后不会把上界抬得更高
                        x -= 1  # 最大值减一，既翻转奇偶又把极差压到最小
                a = min(a, x)  # 维护调整后的最小值
                b = max(b, x)  # 维护调整后的最大值
            return [cnt, max(1, b - a)]  # 长度 ≥ 2 的交替数组不可能所有元素相等，故极差至少为 1

        if len(nums) == 1:  # 单元素数组天然满足交替
            return [0, 0]  # 无需操作，极差为 0

        mn, mx = min(nums), max(nums)  # 预先求出全局最小值和最大值，供内层函数判断最值
        return min(f(0), f(1))  # 先比操作数、再比极差，取字典序更小的方案
