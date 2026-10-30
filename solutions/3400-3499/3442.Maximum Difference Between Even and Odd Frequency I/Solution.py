# 3442. 奇偶频次间的最大差值 I / Maximum Difference Between Even and Odd Frequency I
# 核心思路：用 Counter 统计字母出现次数，取最大奇数次频次 a 与最小偶数次频次 b，答案即 a - b。
# 复杂度：时间 O(n)，空间 O(1)（字母表大小固定）。
class Solution:  # 定义题解类
    def maxDifference(self, s: str) -> int:  # 返回奇数次频次与偶数次频次的最大差值
        cnt = Counter(s)  # 统计每个字母的出现次数
        a, b = 0, inf  # a 为最大奇频次，b 为最小偶频次（初值取无穷大）
        for v in cnt.values():  # 遍历各字母的频次
            if v % 2:  # 频次为奇数
                a = max(a, v)  # 更新最大奇频次
            else:  # 频次为偶数
                b = min(b, v)  # 更新最小偶频次
        return a - b  # 返回最大差值
