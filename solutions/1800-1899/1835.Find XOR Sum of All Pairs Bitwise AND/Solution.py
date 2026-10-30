# 题目：1835. 所有数对按位与结果的异或和（Find XOR Sum of All Pairs Bitwise AND）
# 思路：按位与对异或满足分配律，所有数对按位与的异或和等于两数组各自异或和再按位与。
# 时间复杂度：O(n + m)，两数组各扫描一遍；空间复杂度：O(1)，只用两个整型变量。
class Solution:  # LeetCode 约定的题解类
    def getXORSum(self, arr1: List[int], arr2: List[int]) -> int:  # arr1、arr2 为输入数组，返回所有跨数组数对按位与结果的异或和
        a = reduce(xor, arr1)  # reduce(xor, arr1) 以异或为累积运算，求出 arr1 所有元素的异或和
        b = reduce(xor, arr2)  # 同理求出 arr2 所有元素的异或和
        return a & b  # 两数组异或和相与，就是所有数对按位与结果的异或和
