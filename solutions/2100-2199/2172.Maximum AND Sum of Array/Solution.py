# 题目：2172. 数组的最大与和（Maximum AND Sum of Array）
# 思路：把 numSlots 个槽位拆成 2·numSlots 个格子，用 m 位掩码表示占用情况做状压 DP；第 i.bit_count() 个数放到第 j 个格子。
# 时间复杂度：O(n · 2^m)，m = 2·numSlots；空间复杂度：O(2^m)。
class Solution:  # LeetCode 约定的题解类
    def maximumANDSum(self, nums: List[int], numSlots: int) -> int:  # nums 待分配的数字，numSlots 是槽位个数（每个槽位可容纳两个数）
        n = len(nums)  # 元素个数，最多只需要分配 n 个
        m = numSlots << 1  # 每个槽位拆成两个格子，总计 m 个格子
        f = [0] * (1 << m)  # f[mask]：占用 mask 表示的格子时能得到的最大与和，初始全为 0
        for i in range(1 << m):  # 按掩码从小到大枚举状态（子状态的掩码一定更小，已经被算过）
            cnt = i.bit_count()  # bit_count 统计已占用格子数，正好等于已放入的数字个数
            if cnt > n:  # 已经放满 n 个数，无法再放
                continue  # 该状态不参与转移
            for j in range(m):  # 枚举最后一个放进去的格子 j
                if i >> j & 1:  # 只有被占用的格子才可能是最后一个放进去的
                    f[i] = max(f[i], f[i ^ (1 << j)] + (nums[cnt - 1] & (j // 2 + 1)))  # 从 mask 去掉 j 得到前一状态，再加上 nums[cnt-1] 与第 j//2+1 号槽位的与值
        return max(f)  # 所有可达状态中的最大值即答案（不要求放满）
