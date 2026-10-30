# 题目：3079. 求出加密整数的和（Find the Sum of Encrypted Integers）
# 思路：对每个数求各位数字的最大值 mx，再用同位数全 1 数 p 把 mx 复制满，累加所有加密结果。
# 时间复杂度：O(n·log10 M)，每个数按位处理一次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def sumOfEncryptedInt(self, nums: List[int]) -> int:  # nums 是待加密的整数数组，返回所有加密整数之和
        def encrypt(x: int) -> int:  # 内部函数：按题意加密单个整数 x
            mx = p = 0  # mx 记录各位数字的最大值；p 生成等长全 1 数（1、11、111…）
            while x:  # 逐位取出 x 的每一位，直到 x 变成 0
                x, v = divmod(x, 10)  # v 是当前最低位，x 是去掉最低位后的剩余部分
                mx = max(mx, v)  # 用最低位更新出现过的最大数字
                p = p * 10 + 1  # 每多处理一位就让 p 扩展成 11…1
            return mx * p  # 加密结果：最大数字重复与原数相同的位数

        return sum(encrypt(x) for x in nums)  # 对所有元素加密后求和
