# 题目：3309. 连接二进制表示可形成的最大数值（Maximum Possible Number by Binary Concatenation）
# 思路：三个数的排列一共 3! = 6 种，用 permutations 枚举全部顺序，把每个数的二进制串（去掉 '0b' 前缀）拼起来再按二进制解析，取最大值。
# 复杂度：时间 O(1)，6 种排列、每个数最多 7 位；空间 O(1)，只存常数个中间结果。
class Solution:  # LeetCode 约定的题解类
    def maxGoodNumber(self, nums: List[int]) -> int:  # nums 为三个正整数，返回其二进制表示按任意顺序拼接后能得到的最大数值
        ans = 0  # 记录枚举过程中的最大值
        for arr in permutations(nums):  # 枚举三个数的全部 3! 种排列
            num = int("".join(bin(i)[2:] for i in arr), 2)  # bin(i)[2:] 去掉 '0b' 前缀，拼接后按二进制（base=2）解析成整数
            ans = max(ans, num)  # 更新最大值
        return ans  # 返回最大拼接结果
