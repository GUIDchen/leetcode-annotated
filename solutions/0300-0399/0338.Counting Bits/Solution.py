# 题目：338. 比特位计数（Counting Bits）
# 核心思路：用 Python 3.10+ 的 int.bit_count() 直接数出每个整数二进制中 1 的个数，一次列表推导即可。
# 时间复杂度：O(n log n)，每个整数 bit_count 的代价与其位数成正比（整体视实现约 O(n)）；空间复杂度：O(n)，结果列表长度 n+1。
class Solution:  # LeetCode 约定的题解类
    def countBits(self, n: int) -> List[int]:  # n 为范围上界，返回 0..n 每个整数二进制中 1 的个数
        return [i.bit_count() for i in range(n + 1)]  # 列表推导：对 0..n 的每个 i 调用 int.bit_count() 统计 1 的个数
