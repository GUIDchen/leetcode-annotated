# 题目：377. 组合总和 Ⅳ（Combination Sum IV）
# 思路：完全背包式计数 DP，f[i] 表示凑出和为 i 的排列数，枚举最后一个数 x，累加 f[i - x]。
# 时间复杂度：O(target × n)，n 为 nums 长度；空间复杂度：O(target)，一维 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def combinationSum4(self, nums: List[int], target: int) -> int:  # nums 为可重复使用的数字，target 为目标和，返回能凑出 target 的排列个数
        f = [1] + [0] * target  # f[0] = 1 表示凑出 0 有一种方案（什么都不选），其余先置 0
        for i in range(1, target + 1):  # 按目标和从小到大递推，保证 f[i - x] 已算好
            for x in nums:  # 尝试把 x 当作排列中的最后一个数
                if i >= x:  # i 够大才放得下 x
                    f[i] += f[i - x]  # 剩余部分 i - x 的方案数就是放 x 后新增的排列数
        return f[target]  # 返回凑出 target 的排列个数
