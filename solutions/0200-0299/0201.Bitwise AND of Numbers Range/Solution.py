# 题目：201. 数字范围按位与（Bitwise AND of Numbers Range）
# 思路：区间内所有数按位与就是它们的公共二进制前缀；循环抹掉 right 最低位的 1，直到 left 追上 right。
# 时间复杂度：O(log right)，最多循环 32 次；空间复杂度：O(1)，只用到入参本身。
class Solution:  # LeetCode 约定的题解类
    def rangeBitwiseAnd(self, left: int, right: int) -> int:  # 求闭区间 [left, right] 内所有整数按位与的结果
        while left < right:  # right 还大于 left，说明还有更低的位需要消除
            right &= right - 1  # right &= right - 1 抹掉最低位的 1，因为区间内必有数让这一位为 0
        return right  # 剩下的公共前缀就是答案
