# 题目：1879. 两个数组最小的异或值之和（Minimum XOR Sum of Two Arrays）
# 思路：状压 DP。f[i][j] 表示 nums1 的前 i 个元素与 nums2 中「集合 j 所含下标」配对后的最小异或和，枚举第 i 个元素与集合 j 中的哪个下标 k 配对来转移。
# 时间复杂度：O(n^2 * 2^n)；空间复杂度：O(n * 2^n)，即 DP 表的大小。
class Solution:  # LeetCode 约定的题解类
    def minimumXORSum(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：长度均为 n 的数组；返回所有排列配对方式中最小的异或值之和
        n = len(nums2)  # n：以 nums2 的长度作为状态压缩的规模
        f = [[inf] * (1 << n) for _ in range(n + 1)]  # f[i][j]：nums1 前 i 个元素与集合 j（第 k 位为 1 表示 nums2[k] 已被使用）配对的最小异或和，先全填 inf
        f[0][0] = 0  # 边界：没有元素要配、也没用过任何下标时，异或和为 0
        for i, x in enumerate(nums1, 1):  # 阶段：i 从 1 开始，x 就是当前要配对的 nums1[i-1]
            for j in range(1 << n):  # 状态：枚举所有可能的使用集合 j
                for k in range(n):  # 决策：尝试让 x 与 nums2[k] 配对
                    if j >> k & 1:  # 集合 j 必须包含下标 k（(j >> k) & 1 为 1）才允许这步转移
                        f[i][j] = min(f[i][j], f[i - 1][j ^ (1 << k)] + (x ^ nums2[k]))  # j ^ (1 << k) 把 k 剔除得到上一层状态，再加上本次配对的异或代价
        return f[-1][-1]  # f[n][2^n - 1]：全部配对完成、nums2 所有下标都用过的最优解
