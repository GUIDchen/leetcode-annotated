# 题目：1829. 每个查询的最大异或值（Maximum XOR for Each Query）
# 思路：用 reduce 求出全数组异或和，再从高位到低位把异或和为 0 的位在 k 上置 1；同时倒序遍历 nums 逐个删元素。
# 时间复杂度：O(n * maximumBit)；空间复杂度：O(n)，答案列表。
class Solution:  # LeetCode 约定的题解类
    def getMaximumXor(self, nums: List[int], maximumBit: int) -> List[int]:  # nums：查询数组；maximumBit：答案允许的二进制位数；返回每次查询的最大异或值
        ans = []  # 答案列表
        xs = reduce(xor, nums)  # 整个数组的异或和（reduce 与 xor 由判题器环境提供）
        for x in nums[::-1]:  # 倒序遍历：相当于每次查询前删掉当前末尾元素
            k = 0  # 待构造的 k
            for i in range(maximumBit - 1, -1, -1):  # 从最高位到最低位枚举
                if (xs >> i & 1) == 0:  # 该位为 0 时让 k 的该位取 1，使异或结果该位变成 1
                    k |= 1 << i  # 置位第 i 位
            ans.append(k)  # 记录本次答案
            xs ^= x  # 把该元素从异或和中删除
        return ans  # 返回全部答案
