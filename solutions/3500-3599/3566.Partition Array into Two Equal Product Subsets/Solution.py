# 题目：3566. 等积子集的划分方案（Partition Array into Two Equal Product Subsets）
# 思路：用二进制位掩码枚举所有子集划分，第 j 位为 1 表示 nums[j] 归入第一组；两组各自累乘，枚举完若两组乘积都等于 target 即返回 True。
# 时间复杂度：O(n * 2^n)，枚举 2^n 种划分、每种最多扫 n 个元素；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def checkEqualPartitions(self, nums: List[int], target: int) -> bool:  # nums：待划分的数组；target：两个子集共同的目标乘积；返回能否分成两组且乘积都等于 target
        n = len(nums)  # 记录数组长度，枚举与内层遍历都依赖它
        for i in range(1 << n):  # 枚举全部 2^n 种划分，i 的第 j 位表示 nums[j] 归入哪一组
            x = y = 1  # x、y 分别累乘两组的乘积，初值取乘法单位元 1
            for j in range(n):  # 逐个元素按当前掩码分配
                if i >> j & 1:  # 取 i 的第 j 位，为真表示 nums[j] 划入第一组
                    x *= nums[j]  # 第一组的乘积乘上该元素
                else:  # 否则该元素划入第二组
                    y *= nums[j]  # 第二组的乘积乘上该元素
            if x == target and y == target:  # 两组乘积都恰好等于 target，说明该划分成立
                return True  # 返回真
        return False  # 所有划分都不成立，返回假
