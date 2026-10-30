# 题目：260. 只出现一次的数字 III（Single Number III）
# 思路：位运算分组。reduce(xor, nums) 得到 a^b，取最低位的 1 作为区分位，把数分成两组分别异或得到 a 与 b。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个变量。

class Solution:  # LeetCode 约定的题解类
    def singleNumber(self, nums: List[int]) -> List[int]:  # nums：只有两个数出现一次，其余数都出现两次
        xs = reduce(xor, nums)  # 全部异或：成对的数抵消，结果就是 a ^ b
        a = 0  # 用来累计其中一组内所有数的异或和
        lb = xs & -xs  # 取最低位的 1 作为区分位：a 与 b 在这一位上必然不同
        for x in nums:  # 第二遍遍历，按区分位分组
            if x & lb:  # 只处理该位为 1 的那一组
                a ^= x  # 组内成对的数抵消，剩下就是 a
        b = xs ^ a  # 由 a ^ b 与 a 反推出 b
        return [a, b]  # 返回两个只出现一次的数
