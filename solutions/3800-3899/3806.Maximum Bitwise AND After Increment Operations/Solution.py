# 题目：3806. 增加操作后最大按位与的结果（Maximum Bitwise AND After Increment Operations）
# 思路：从高位到低位贪心确定答案的每一位；计算把每个数补成 target 超集的最小增量，取最小的 m 个看总增量是否超过 k。
# 时间复杂度：O(32 · n log n)，每个二进制位排序一次代价数组；空间复杂度：O(n)，存放每个数的最小增量。
class Solution:  # LeetCode 约定的题解类
    def maximumAND(self, nums: List[int], k: int, m: int) -> int:  # 总共可以加 k，从中选 m 个数使按位与最大，返回该最大值
        mx = (max(nums) + k).bit_length()  # 单个元素加完 k 之后最大可能值的二进制位数，决定要枚举的位范围
        ans = 0  # 从高位到低位逐位确定答案
        cost = [0] * len(nums)  # 把每个数变成当前 target 的超集所需的最小增量
        for bit in range(mx - 1, -1, -1):  # 从最高位开始，贪心地尝试把这一位设为 1
            target = ans | (1 << bit)  # 假设答案在这一位可取 1 后的目标值
            for i, x in enumerate(nums):  # 计算每个数的代价
                j = (target & ~x).bit_length()  # target 有、而 x 没有的位的最高位置 + 1（为 0 表示不用加）
                mask = (1 << j) - 1  # 只保留到这个最高位的掩码
                cost[i] = (target & mask) - (x & mask)  # 只改低位就能让 x 覆盖 target 的这些位，所需增量即两段之差
            cost.sort()  # 按代价升序排列，贪心地选最便宜的前 m 个
            if sum(cost[:m]) <= k:  # 前 m 小的代价之和不超过 k，说明这一位可以保留
                ans = target  # 确认这一位为 1
        return ans  # 返回能得到的最大按位与
