# 3836. 恰好 K 个下标对的最大得分 / Maximum Score Using Exactly K Pairs（困难）
# 核心思路：三维 DP，f[i][j][k] 表示 nums1 前 i 个元素与 nums2 前 j 个元素中恰好选出 k 个不交叉下标对的最大得分；每个状态可跳过 nums1[i-1]、跳过 nums2[j-1]，或让两者配成一对（乘积累加）。
# 复杂度：时间 O(n*m*K)，空间 O(n*m*K)。
class Solution:  # LeetCode 要求的类名
    def maxScore(self, nums1: List[int], nums2: List[int], K: int) -> int:  # 返回恰好 K 对下标配对的最大得分
        n, m = len(nums1), len(nums2)  # 两个数组的长度
        f = [[[-inf] * (K + 1) for _ in range(m + 1)] for _ in range(n + 1)]  # f[i][j][k]：两个前缀中恰好选出 k 对的最大得分，整体初始化为负无穷
        f[0][0][0] = 0  # 空前缀选 0 对，得分为 0（合法起点）
        for i in range(n + 1):  # 枚举 nums1 的前缀长度
            for j in range(m + 1):  # 枚举 nums2 的前缀长度
                for k in range(K + 1):  # 枚举已经选出的下标对数
                    if i > 0:  # 允许完全不使用 nums1 的最后一个元素
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j][k])  # 继承 i-1 的状态，即 nums1[i-1] 不参与配对
                    if j > 0:  # 允许完全不使用 nums2 的最后一个元素
                        f[i][j][k] = max(f[i][j][k], f[i][j - 1][k])  # 继承 j-1 的状态，即 nums2[j-1] 不参与配对
                    if i > 0 and j > 0 and k > 0:  # 两个前缀都非空，且还需要再凑出一对
                        f[i][j][k] = max(  # 尝试把 nums1[i-1] 与 nums2[j-1] 配成第 k 对
                            f[i][j][k],  # 保留之前（跳过某一侧）得到的更优值
                            f[i - 1][j - 1][k - 1] + nums1[i - 1] * nums2[j - 1],  # 前 k-1 对的最优解加上这对的乘积
                        )  # 配对表达式结束
        return f[n][m][K]  # 两个完整数组恰好 K 对的最大得分
