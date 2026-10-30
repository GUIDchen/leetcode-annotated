# 题目：1093. 大样本统计（Statistics from a Large Sample）
# 思路：count[k] 表示数值 k 出现的次数。一次遍历求出最小/最大值、总和、样本总数与众数；中位数用前缀和定位（find 找第 i 个样本落在哪个值），偶数个时取中间两个的平均。
# 时间复杂度：O(V)，V = 256 为取值个数（find 最多调用两次，每次最坏扫 V 个值）；空间复杂度：O(1)，只用常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def sampleStats(self, count: List[int]) -> List[float]:  # count[k] 是数值 k 的出现次数，返回 [最小值, 最大值, 均值, 中位数, 众数]
        def find(i: int) -> int:  # 内层函数：返回第 i 个样本（1-based）落在哪个数值上
            t = 0  # 累计样本数
            for k, x in enumerate(count):  # 从小到大枚举数值 k 及其出现次数 x
                t += x  # 累加出现次数
                if t >= i:  # 累计个数已经覆盖到第 i 个样本
                    return k  # 这个数值就是答案

        mi, mx = inf, -1  # inf 作为最小值初值（任意真实值都比它小），-1 表示最大值尚未出现
        s = cnt = 0  # s 为所有样本之和，cnt 为样本总数
        mode = 0  # 众数的数值，先默认 0
        for k, x in enumerate(count):  # 遍历所有可能取值
            if x:  # 只统计出现过（次数大于 0）的数值
                mi = min(mi, k)  # 更新最小值
                mx = max(mx, k)  # 更新最大值
                s += k * x  # 累加「数值 × 出现次数」
                cnt += x  # 累加样本总数
                if x > count[mode]:  # 出现次数严格大于当前众数的次数
                    mode = k  # 更新众数；相等时保留较小的数值，符合题目要求

        median = (  # 中位数：奇数个取正中间那个，偶数个取中间两个的平均
            find(cnt // 2 + 1) if cnt & 1 else (find(cnt // 2) + find(cnt // 2 + 1)) / 2  # cnt & 1 判断奇数；cnt // 2 + 1 是第几个样本（1-based）
        )  # 三元表达式结束
        return [mi, mx, s / cnt, median, mode]  # 按题目要求顺序返回最小、最大、均值、中位数、众数
