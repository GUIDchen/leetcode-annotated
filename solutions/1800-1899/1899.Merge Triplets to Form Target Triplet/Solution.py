# 题目：1899. 合并若干三元组以形成目标三元组（Merge Triplets to Form Target Triplet）
# 思路：任一维超过 target 的三元组都不能参与合并（合并只会让分量变大），在剩余三元组里逐维取最大值，恰等于 target 时即可形成目标。
# 时间复杂度：O(m)，m 为三元组个数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def mergeTriplets(self, triplets: List[List[int]], target: List[int]) -> bool:  # triplets：可选三元组；target：目标三元组
        x, y, z = target  # 拆出目标的三个分量
        d = e = f = 0  # 各维能取到的最大值
        for a, b, c in triplets:  # 逐个考察三元组
            if a <= x and b <= y and c <= z:  # 任一维超过目标的三元组不能参与合并
                d = max(d, a)  # 更新第一维最大值
                e = max(e, b)  # 更新第二维最大值
                f = max(f, c)  # 更新第三维最大值
        return [d, e, f] == target  # 三个分量都顶到目标值即可形成目标三元组
