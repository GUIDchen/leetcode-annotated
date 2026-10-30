# 题目：2778. 特殊元素平方和（Sum of Squares of Special Elements）
# 思路：用 enumerate 从 1 开始给元素编号，编号 i 能整除长度 n 的元素就是特殊元素，把它的平方求和即可。
# 时间复杂度：O(n)，遍历一次数组；空间复杂度：O(1)，生成器不额外保存数据。
class Solution:  # LeetCode 约定的题解类
    def sumOfSquares(self, nums: List[int]) -> int:  # nums 是输入数组
        n = len(nums)  # 数组长度，同时作为判断整除的模数
        return sum(x * x for i, x in enumerate(nums, 1) if n % i == 0)  # 1 起编号 i，仅当 n 能被 i 整除时把该元素的平方计入总和
