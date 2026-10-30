# 题目：3277. 查询子数组最大异或分数（Maximum XOR Score Subarray Queries）
# 思路：区间异或分数可递推 f[i][j] = f[i][j-1] ^ f[i+1][j]，再用 g[i][j] 维护子区间最大值，实现 O(1) 查询。
# 时间复杂度：O(n^2 + q)，预处理所有区间后每次查询 O(1)；空间复杂度：O(n^2)，两张二维表。
class Solution:  # LeetCode 约定的题解类
    def maximumSubarrayXor(  # nums：原数组；queries：若干查询区间
        self, nums: List[int], queries: List[List[int]]  # self 是实例本身，nums 与 queries 是题目入参
    ) -> List[int]:  # 返回每个查询对应的最大异或分数
        n = len(nums)  # 数组长度
        f = [[0] * n for _ in range(n)]  # f[i][j]：nums[i..j] 这个区间本身的异或分数
        g = [[0] * n for _ in range(n)]  # g[i][j]：nums[i..j] 所有子区间的最大异或分数
        for i in range(n - 1, -1, -1):  # 倒序枚举左端点，保证依赖的更短区间已经算好
            f[i][i] = g[i][i] = nums[i]  # 单元素区间的分数与最大分数都等于元素本身
            for j in range(i + 1, n):  # 枚举右端点
                f[i][j] = f[i][j - 1] ^ f[i + 1][j]  # 区间分数递推：去掉右端点的分数异或去掉左端点的分数
                g[i][j] = max(f[i][j], g[i][j - 1], g[i + 1][j])  # 最大分数来自：本区间、去掉右端点、去掉左端点
        return [g[l][r] for l, r in queries]  # 直接用预处理表回答每个查询
