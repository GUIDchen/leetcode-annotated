# 题目：287. 寻找重复数（Find the Duplicate Number）—— 长度 n+1、取值在 [1, n] 的数组里恰有一个数重复，找出它。
# 核心思路：对答案值域二分。判定函数 f(x) = (nums 中 <= x 的个数 > x)，它在答案左侧为 False、右侧为 True，取其第一个 True。
# 时间复杂度：O(n log n)，每次判定扫一遍数组；空间复杂度：O(1)，不修改数组、只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findDuplicate(self, nums: List[int]) -> int:  # nums：n+1 个元素、取值在 [1, n]，其中恰有一个数重复
        def f(x: int) -> bool:  # 判定函数：答案是否 <= x
            return sum(v <= x for v in nums) > x  # 抽屉原理：若 <= x 的元素多于 x 个，重复数必然落在 [1, x] 内

        return bisect_left(range(len(nums)), True, key=f)  # 在 0..len(nums)-1 上二分第一个使 f 为 True 的下标，该下标即重复数（bisect_left 支持 key 回调）
