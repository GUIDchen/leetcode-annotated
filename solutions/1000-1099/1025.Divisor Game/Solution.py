# 题目：1025. 除数博弈（Divisor Game）
# 思路：奇数 n 的所有因数都是奇数，n - x 必为偶数；偶数一步就能减成奇数，所以偶数必胜、奇数必败。
# 时间复杂度：O(1)，只做一次取模；空间复杂度：O(1)，不需要额外空间。
class Solution:  # LeetCode 约定的题解类
    def divisorGame(self, n: int) -> bool:  # n：初始数字；返回先手 Alice 是否能赢
        return n % 2 == 0  # 偶数返回 True（先手胜），奇数返回 False（先手败）
