# 题目：1863. 找出所有子集的异或总和再求和（Sum of All Subset XOR Totals）
# 思路：用二进制数 i 枚举全部 2^n 个子集，i 的第 j 位为 1 表示选入 nums[j]，算出该子集异或和再累加。
# 时间复杂度：O(2^n · n)，枚举子集与逐元素的二重循环；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def subsetXORSum(self, nums: List[int]) -> int:  # nums：输入数组
        ans, n = 0, len(nums)  # ans 是答案累加器，n 是元素个数（子集总数为 2^n）
        for i in range(1 << n):  # 用 i 的二进制位表示一个子集，共 1 << n 个
            s = 0  # 当前子集的异或和，0 是异或的单位元
            for j in range(n):  # 逐位检查第 j 个元素是否被选中
                if i >> j & 1:  # 第 j 位为 1 表示 nums[j] 属于当前子集
                    s ^= nums[j]  # 把 nums[j] 异或进当前结果
            ans += s  # 累加当前子集的异或和
        return ans  # 返回所有子集异或和的总和
