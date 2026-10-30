# 题目：1015. 可被 K 整除的最小整数（Smallest Integer Divisible by K）
# 思路：全 1 数只需用余数演化：n = (n * 10 + 1) % k。长度最多试 k 次，一旦余数为 0 即为答案，试满 k 次仍无解则不存在。
# 时间复杂度：O(k)，最多循环 k 次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def smallestRepunitDivByK(self, k: int) -> int:  # k：给定的正整数除数
        n = 1 % k  # 长度为 1 的全 1 数对 k 的余数（k 为 1 时直接为 0）
        for i in range(1, k + 1):  # 长度从 1 试到 k：这 k 个余数若都不为 0 就必然有重复，答案不存在
            if n == 0:  # 当前这个全 1 数能被 k 整除
                return i  # 返回它的位数，即最小的长度
            n = (n * 10 + 1) % k  # 末尾再添一个 1 后继续取模，只保留余数
        return -1  # 不存在这样的整数
