# 题目：2894. 分类求和并作差（Divisible and Non-divisible Sums Difference）
# 思路：用生成器一次遍历 1..n，能被 m 整除的数取 -i、否则取 +i，求和即得 num1 - num2。
# 时间复杂度：O(n)，只遍历一遍；空间复杂度：O(1)，生成器不额外存储序列。
class Solution:  # LeetCode 约定的题解类
    def differenceOfSums(self, n: int, m: int) -> int:  # n：上界；m：除数
        return sum(i if i % m else -i for i in range(1, n + 1))  # 遍历 1..n：不能被 m 整除时取 +i，能被整除时取 -i，再整体求和
