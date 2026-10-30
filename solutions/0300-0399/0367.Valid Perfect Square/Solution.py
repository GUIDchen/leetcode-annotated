# 题目：367. 有效的完全平方数（Valid Perfect Square）
# 思路：二分查找 [1, num] 中第一个 x*x >= num 的位置，取到下标后再加 1 还原成实际的 x，最后判断 x*x 是否等于 num。
# 时间复杂度：O(log num)，二分次数；空间复杂度：O(1)，只存一个下标。
class Solution:  # LeetCode 约定的题解类
    def isPerfectSquare(self, num: int) -> bool:  # num 是待判断的正整数，返回它是否为完全平方数
        l = bisect_left(range(1, num + 1), num, key=lambda x: x * x) + 1  # bisect_left 返回第一个 x*x >= num 的下标（从 0 起），加 1 得到真实候选值
        return l * l == num  # 候选值的平方若恰好等于 num 则是完全平方数
