# 题目：2614. 对角线上的质数（Prime In Diagonal）
# 思路：逐行同时取出主对角线元素 row[i] 与副对角线元素 row[n-1-i]，用试除法判质数并取最大值。
# 时间复杂度：O(n * sqrt(V))，V 为矩阵中的最大数；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def diagonalPrime(self, nums: List[List[int]]) -> int:  # nums 是 n x n 矩阵；返回两条对角线上最大的质数，没有则返回 0
        def is_prime(x: int) -> bool:  # 判断 x 是否为质数
            if x < 2:  # 0、1 与负数都不是质数
                return False  # 直接判否
            return all(x % i for i in range(2, int(sqrt(x)) + 1))  # 枚举到 sqrt(x)：没有任何整除数时 all 返回 True，即 x 为质数

        n = len(nums)  # 矩阵边长
        ans = 0  # 记录目前找到的最大质数，0 表示还没找到
        for i, row in enumerate(nums):  # 同时取得行下标与整行数据
            if is_prime(row[i]):  # 主对角线元素（行下标等于列下标）
                ans = max(ans, row[i])  # 是质数就更新答案
            if is_prime(row[n - i - 1]):  # 副对角线元素（列下标为 n - 1 - i）
                ans = max(ans, row[n - i - 1])  # 是质数就更新答案
        return ans  # 没有任何质数时自然返回 0
