# 题目：2481. 分割圆的最少切割次数（Minimum Cuts to Divide a Circle）
# 思路：n == 1 不用切；n 为偶数时每条直径一刀切出两块，共 n/2 刀；n 为奇数时每个点只能单独引一条半径，共 n 刀。
# 时间复杂度：O(1)，只做常数次判断；空间复杂度：O(1)，只用常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfCuts(self, n: int) -> int:  # n：要把圆分成的等份数；返回最少切割次数
        return n if (n > 1 and n & 1) else n >> 1  # n>1 且为奇数需 n 刀；否则取 n//2（n==1 时得 0，偶数时一条直径算一刀）
