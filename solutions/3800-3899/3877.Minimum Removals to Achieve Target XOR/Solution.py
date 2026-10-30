# 3877. 达到目标异或值的最少删除次数（Minimum Removals to Achieve Target XOR）
# 核心思路：删除次数最少等价于保留元素最多。先确定异或值需要的二进制位数 m；用 f[i][j] 表示前 i 个数中异或和为 j 时最多能保留多少个元素，最终答案是 n - f[n][target]。
# 复杂度：时间复杂度 O(n·2^m)，空间复杂度 O(n·2^m)。
class Solution:  # 题解类
    def minRemovals(self, nums: List[int], target: int) -> int:  # 返回使异或和等于 target 的最少删除次数
        m = max(nums).bit_length()  # 最大元素的二进制位数，即可能的异或和所需位数
        if (1 << m) <= target:  # target 超出所有可能异或和的取值范围
            return -1  # 无论怎么删都无法得到 target
        n = len(nums)  # 数组长度
        f = [[-inf] * (1 << m) for _ in range(n + 1)]  # f[i][j]：前 i 个数异或和为 j 时最多保留的元素个数
        f[0][0] = 0  # 空集异或和为 0，保留 0 个元素
        for i, x in enumerate(nums, 1):  # 逐个考虑数组元素，下标从 1 开始
            for j in range(1 << m):  # 枚举所有可能的异或和
                f[i][j] = max(f[i - 1][j], f[i - 1][j ^ x] + 1)  # 不选 x 或选 x（选则保留数加一）
        if f[n][target] < 0:  # 没有任何子集的异或和等于 target
            return -1  # 无法达成目标
        return n - f[n][target]  # 总个数减去最多保留的个数即为最少删除次数
