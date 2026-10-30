# 3852. 不同频率的最小数对 / Smallest Pair With Different Frequencies（简单）
# 核心思路：统计每个值的出现次数，字典序最优的左端必然是全局最小值 x，再在其余出现过的值中挑出频次与 cnt[x] 不同的最小 y，找不到则返回 [-1, -1]。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 设计一个算法：找频率不同的最小数对 (x, y)
    def minDistinctFreqPair(self, nums: list[int]) -> list[int]:  # 返回满足 x < y 且频次不同的最小数对，无解时返回 [-1, -1]
        cnt = Counter(nums)  # 统计每个值出现的次数
        x = min(cnt.keys())  # x 取最小值：它作数对左端时字典序必然最小
        min_y = inf  # 在剩余值中找频次与 cnt[x] 不同的最小 y，inf 表示未找到
        for y in cnt.keys():  # 遍历所有出现过的值
            if y < min_y and cnt[x] != cnt[y]:  # 比当前候选更小，且频次与 x 不同
                min_y = y  # 更新更小的 y
        return [-1, -1] if min_y == inf else [x, min_y]  # 无解返回 [-1, -1]，否则返回字典序最小的合法数对
