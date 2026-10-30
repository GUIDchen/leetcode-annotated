# 题目：3232. 判断是否可以赢得数字游戏（Find if Digit Game Can Be Won）
# 思路：Alice 只能取一位数、Bob 只能取两位数，两人的可选集合固定；只要两组之和不等，Alice 选择较大的那一组即可获胜。
# 时间复杂度：O(n)，一次遍历求和；空间复杂度：O(1)，只用两个累加变量。
class Solution:  # LeetCode 约定的题解类
    def canAliceWin(self, nums: List[int]) -> bool:  # nums：可选数字；返回先手 Alice 是否能赢
        a = sum(x for x in nums if x < 10)  # Alice 只能拿一位数，对它们求和
        b = sum(x for x in nums if x > 9)  # Bob 只能拿两位数，对它们求和
        return a != b  # 两组之和不等时，Alice 选择较大的一组即可获胜
