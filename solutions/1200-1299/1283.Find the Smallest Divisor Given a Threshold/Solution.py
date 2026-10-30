# 题目：1283. 使结果不超过阈值的最小除数（Find the Smallest Divisor Given a Threshold）
# 思路：答案具有单调性——除数越大，向上取整之和越小，于是把「除数 - 1」作为搜索下标交给 bisect_left 二分第一个可行位置。
# 时间复杂度：O(n·log max(nums))，每次判定扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:  # 返回使向上取整之和不超过 threshold 的最小除数
        def f(v: int) -> bool:  # 判定函数：参数 v 是「除数 - 1」，即真正使用的除数是 v + 1
            v += 1  # 先还原成真正的除数
            return sum((x + v - 1) // v for x in nums) <= threshold  # 整数除法实现向上取整，再判断和是否不超过阈值

        return bisect_left(range(max(nums)), True, key=f) + 1  # 在 0..max-1 上二分第一个判定为真的下标，加 1 得到除数
