# 题目：2413. 最小偶倍数（Smallest Even Multiple）
# 思路：n 为偶数时最小偶倍数就是 n 本身；n 为奇数时最小偶倍数是 n*2，用条件表达式一次判断即可。
# 时间复杂度：O(1)，只有一次取模与一次乘法；空间复杂度：O(1)，不使用额外存储。
class Solution:  # LeetCode 约定的题解类
    def smallestEvenMultiple(self, n: int) -> int:  # n 是给定的正整数，返回它的最小正偶倍数
        return n if n % 2 == 0 else n * 2  # 偶数直接返回 n，奇数返回 2*n
