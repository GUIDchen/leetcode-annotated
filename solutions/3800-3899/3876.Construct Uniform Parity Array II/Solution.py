# 3876. 构造奇偶一致的数组 II（Construct Uniform Parity Array II）
# 核心思路：所有奇数都能被最小的那个奇数「消成」偶数，所以只需找出最小奇数 mn；只要每个偶数都不小于 mn，就能通过减法把整个数组变成偶数，否则无解。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # 题解类
    def uniformArray(self, nums1: List[int]) -> bool:  # 判断能否把所有元素统一成同一种奇偶性
        mn = min((x for x in nums1 if x & 1), default=None)  # 找出所有奇数中的最小值，没有奇数时为 None
        return mn is None or all(x >= mn for x in nums1 if x & 1 == 0)  # 无奇数则必然可行；否则要求偶数都不小于最小奇数（按原代码保留：Python 中 == 优先级高于 &）
