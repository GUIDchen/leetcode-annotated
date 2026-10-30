# 题目：3077. K 个不相交子数组的最大能量值（Maximum Strength of K Disjoint Subarrays）
# 思路：线性 DP。f[i][j][t] 表示「考虑前 i 个数、已凑出 j 个子数组、t 表示第 i 个数是否属于第 j 段」时的最大能量，逐元素做「不选 / 延续当前段 / 新开一段」三种转移。
# 时间复杂度：O(nk)，每个状态只做常数次转移；空间复杂度：O(nk)，用三维列表保存全部状态。
class Solution:  # LeetCode 约定的题解类
    def maximumStrength(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：需要选择的子数组个数；返回最大能量值
        n = len(nums)  # 数组长度
        f = [[[-inf, -inf] for _ in range(k + 1)] for _ in range(n + 1)]  # f[i][j][t]：考虑前 i 个数、恰好选了 j 段，t=1 表示第 i 个数在第 j 段内；-inf 表示不可达
        f[0][0][0] = 0  # 边界：前 0 个数选 0 段且不在任何段中，能量为 0
        for i, x in enumerate(nums, 1):  # 从下标 1 开始枚举，i 表示考虑到前 i 个数，x 是新增的元素 nums[i-1]
            for j in range(k + 1):  # 枚举已经凑出的子数组段数 j
                sign = 1 if j & 1 else -1  # 第 j 段的符号：j 为奇数取正、偶数取负，即 (-1)^(j+1)
                f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1])  # 不把第 i 个数纳入任何段：从上一轮「不在段中」或「正在段中」两种状态取较优者
                f[i][j][1] = max(f[i][j][1], f[i - 1][j][1] + sign * x * (k - j + 1))  # 延续第 j 段：接到上一轮「正在第 j 段中」的状态后面并加上当前贡献，与已有值取较大者
                if j:  # 只有已经选了至少一段，才能考虑新开第 j 段
                    f[i][j][1] = max(  # 新开一段：在上一轮已选 j-1 段的最优状态之上，把当前元素作为新段的一部分
                        f[i][j][1], max(f[i - 1][j - 1]) + sign * x * (k - j + 1)  # 候选一：保持原值；候选二：上一轮 j-1 段的最优值 + 当前元素贡献
                    )  # 两个候选取较大者作为最终状态
        return max(f[n][k])  # 答案：前 n 个数正好选了 k 段，最后一个数在段内或段外都允许，取较大者
