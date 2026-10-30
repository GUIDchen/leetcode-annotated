# 题目：1980. 找出不同的二进制字符串（Find Unique Binary String）
# 思路：长度为 n 的串最多只有 n+1 种「1 的个数」，用位掩码记下已出现的个数，取第一个空缺 i，构造 i 个 1 加 n-i 个 0 即可。
# 时间复杂度：O(n^2)，统计 1 与构造字符串；空间复杂度：O(1)，只用一个整数掩码。
class Solution:  # LeetCode 约定的题解类
    def findDifferentBinaryString(self, nums: List[str]) -> str:  # nums 是 n 个长度为 n 的二进制串，返回一个不在其中的同长度串
        mask = 0  # 位掩码：第 k 位为 1 表示已存在「恰好 k 个 1」的字符串
        for x in nums:  # 遍历给定的每个字符串
            mask |= 1 << x.count("1")  # 统计 '1' 的个数，并把对应的计数位置 1
        for i in count(0):  # 从 0 开始无限递增（count 来自 itertools），找第一个没被占用的计数 i
            if mask >> i & 1 ^ 1:  # 该位为 0（异或 1 后为真）说明没有串只含 i 个 '1'
                return "1" * i + "0" * (len(nums) - i)  # 构造 i 个 '1' 加 n-i 个 '0'，必然不同于任何给定串
