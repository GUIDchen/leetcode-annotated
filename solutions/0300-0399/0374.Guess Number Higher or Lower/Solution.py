# 题目：374. 猜数字大小（Guess Number Higher or Lower）
# 思路：答案落在 [1, n]，用 bisect 在单调 key 上二分，找到 guess 返回 0 的位置即答案。
# 时间复杂度：O(log n)，二分查找；空间复杂度：O(1)，只在 range 上做逻辑二分。
# The guess API is already defined for you.
# @param num, your guess
# @return -1 if num is higher than the picked number
#          1 if num is lower than the picked number
#          otherwise return 0
# def guess(num: int) -> int:


class Solution:  # LeetCode 约定的题解类
    def guessNumber(self, n: int) -> int:  # n 为数字上限，返回被选中的那个数字
        return bisect.bisect(range(1, n + 1), 0, key=lambda x: -guess(x))  # key 取 -guess(x) 把返回值转成随 x 递增的序列，bisect 查到 0 的落点即被选中的数字
