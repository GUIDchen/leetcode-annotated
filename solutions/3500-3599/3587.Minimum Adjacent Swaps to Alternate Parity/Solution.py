# 3587. 最小相邻交换至奇偶交替（Minimum Adjacent Swaps to Alternate Parity）
# 核心思路：记录奇偶元素各自的下标，若数量差超过 1 则无解；否则让较少的一类（或两类取优）依次填满目标奇偶位，交换次数等于下标位移之和。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为数组长度。
class Solution:  # 定义题解类
    def minSwaps(self, nums: List[int]) -> int:  # 求使奇偶交替的最少相邻交换次数
        def calc(k: int) -> int:  # 计算把 k 类元素依次放到下标 0,2,4... 上的交换代价
            return sum(abs(i - j) for i, j in zip(range(0, len(nums), 2), pos[k]))  # 目标下标与元素原下标的差之和即为交换次数

        pos = [[], []]  # pos[0] 存偶数下标，pos[1] 存奇数下标
        for i, x in enumerate(nums):  # 遍历数组，按下标收集两类元素的位置
            pos[x & 1].append(i)  # 把当前下标放入对应奇偶性的位置表
        if abs(len(pos[0]) - len(pos[1])) > 1:  # 两类数量差超过 1 时无法交替排列
            return -1  # 返回无解
        if len(pos[0]) > len(pos[1]):  # 偶数更多时只能从偶数开始交替
            return calc(0)  # 返回偶数占奇数位的方案
        if len(pos[0]) < len(pos[1]):  # 奇数更多时只能从奇数开始交替
            return calc(1)  # 返回奇数占奇数位的方案
        return min(calc(0), calc(1))  # 两类数量相等时两种方案取更小值
