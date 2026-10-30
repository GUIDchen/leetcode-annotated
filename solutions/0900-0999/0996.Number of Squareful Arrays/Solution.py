# 题目：996. 平方数组的数目（Number of Squareful Arrays）
# 思路：状压 DP，f[i][j] 表示已选下标集合 i、以 j 结尾且相邻两数之和都是完全平方数的排列数；最后按各值出现次数的阶乘做多重集去重。
# 时间复杂度：O(2^n · n^2)，空间复杂度：O(2^n · n)。
class Solution:  # LeetCode 约定的题解类
    def numSquarefulPerms(self, nums: List[int]) -> int:  # nums：输入数组；返回相邻元素之和全为完全平方数的不同排列数目
        n = len(nums)  # 数组长度，n ≤ 12，因此 2^n 状压可行
        f = [[0] * n for _ in range(1 << n)]  # f[i][j]：已选下标集合为 i、末尾元素为 nums[j] 的合法排列数
        for j in range(n):  # 初始化只含一个元素的集合
            f[1 << j][j] = 1  # 只选 j 且以 j 结尾，方案数为 1
        for i in range(1 << n):  # 从小到大枚举所有选中的下标集合
            for j in range(n):  # 枚举集合 i 中作为排列末尾的元素 j
                if i >> j & 1:  # 第 j 位为 1 才说明 j 在集合 i 中
                    for k in range(n):  # 枚举接在 j 前面的元素 k
                        if (i >> k & 1) and k != j:  # k 也必须在集合 i 里，且不能与 j 重复
                            s = nums[j] + nums[k]  # 相邻两元素之和
                            t = int(sqrt(s))  # 向下取整开平方，用于判断完全平方数
                            if t * t == s:  # 平方后能还原，说明是相邻合法的完全平方数
                                f[i][j] += f[i ^ (1 << j)][k]  # 由去掉 j 的集合状态转移而来（同值会重复累加，最后统一去重）

        ans = sum(f[(1 << n) - 1][j] for j in range(n))  # (1<<n)-1 是全集；累加以各元素结尾的排列数
        for v in Counter(nums).values():  # 遍历每个不同值的出现次数
            ans //= factorial(v)  # 多重集去重：相同值的 v! 种交换视为同一种排列
        return ans  # 返回去重后的合法排列总数
