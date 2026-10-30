# 题目：2552. 统计上升四元组（Count Increasing Quadruplets）
# 思路：枚举中间下标 j、k。f[j][k] 统计 i < j 且 nums[i] < nums[k] 的 i 的个数，g[j][k] 统计 l > k 且 nums[l] > nums[j] 的 l 的个数，两者相乘即该 (j, k) 贡献的四元组数；计数用「先扫一遍一侧、再沿下标移动动态扣减」维护。
# 时间复杂度：O(n^2)，两轮 O(n^2) 的扫描；空间复杂度：O(n^2)，两张 n x n 的计数表。
class Solution:  # LeetCode 约定的题解类
    def countQuadruplets(self, nums: List[int]) -> int:  # nums 是 1..n 的一个排列
        n = len(nums)  # n 是数组长度
        f = [[0] * n for _ in range(n)]  # f[j][k]：满足 i < j 且 nums[i] < nums[k] 的 i 的个数
        g = [[0] * n for _ in range(n)]  # g[j][k]：满足 l > k 且 nums[l] > nums[j] 的 l 的个数
        for j in range(1, n - 2):  # 枚举第二个下标 j（前后都要留位置：1 ≤ j ≤ n-3）
            cnt = sum(nums[l] > nums[j] for l in range(j + 1, n))  # 先统计所有 l > j 且 nums[l] > nums[j] 的个数，作为 cnt 的初值
            for k in range(j + 1, n - 1):  # 枚举第三个下标 k（j < k < n-1），从左往右移动
                if nums[j] > nums[k]:  # nums[j] > nums[k] 时 f[j][k] 才有意义
                    f[j][k] = cnt  # 此时 cnt 正好是 l > k 的个数，直接写入 f[j][k]
                else:  # 否则 nums[k] > nums[j]
                    cnt -= 1  # nums[k] 曾被计入 cnt，k 右移后不再属于 l > k，故减一
        for k in range(2, n - 1):  # 枚举第三个下标 k（左侧至少两个位置：k ≥ 2）
            cnt = sum(nums[i] < nums[k] for i in range(k))  # 先统计所有 i < k 且 nums[i] < nums[k] 的个数，作为 cnt 的初值
            for j in range(k - 1, 0, -1):  # 枚举第二个下标 j，从 k-1 向左扫到 1
                if nums[j] > nums[k]:  # nums[j] > nums[k] 时 g[j][k] 才有意义
                    g[j][k] = cnt  # 此时 cnt 正好是 i < j 的个数，写入 g[j][k]
                else:  # 否则 nums[j] < nums[k]
                    cnt -= 1  # j 向左移出后不再属于 i < j，且它被计入过 cnt，故减一
        return sum(  # 对所有 (j, k) 把左右两侧的数量相乘再求和，即四元组总数
            f[j][k] * g[j][k] for j in range(1, n - 2) for k in range(j + 1, n - 1)  # 生成器表达式遍历每一组 j < k，累加 f[j][k] * g[j][k]
        )
