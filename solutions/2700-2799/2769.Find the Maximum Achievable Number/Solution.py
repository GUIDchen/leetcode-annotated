# 题目：2769. 找出最大的可达成数字（Find the Maximum Achievable Number）
# 思路：每次操作让 num 加 1、同时让 x 减 1，一次操作把两者差距缩小 2，所以 t 次操作后 x 最大为 num + 2t。
# 时间复杂度：O(1)，一次乘加即可；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def theMaximumAchievableX(self, num: int, t: int) -> int:  # num 是起始数字，t 是允许的操作次数
        return num + t * 2  # 每次操作贡献 2 的差距，t 次后 x 的最大取值
