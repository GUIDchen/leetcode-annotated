# 3431. Minimum Unlocked Indices to Sort Nums / 3431. 对数字排序的最小解锁下标
# 核心思路：先用 3 是否出现在 1 之前判定无解，再统计落在 (first2, last1) 或 (first3, last2) 内的锁定下标。
# 复杂度：时间 O(n)，空间 O(1)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def minUnlockedIndices(self, nums: List[int], locked: List[int]) -> int:  # 返回使 nums 非递减有序所需解锁的最少下标个数
        n = len(nums)  # 数组长度 n
        first2 = first3 = n  # 记录 2 与 3 第一次出现的位置，初值 n 表示不存在
        last1 = last2 = -1  # 记录 1 与 2 最后一次出现的位置，初值 -1 表示不存在
        for i, x in enumerate(nums):  # 第一遍扫描：统计 1、2、3 各自的首末位置
            if x == 1:  # 遇到数值 1
                last1 = i  # 更新 1 的最后一次出现位置
            elif x == 2:  # 遇到数值 2
                first2 = min(first2, i)  # 更新 2 的第一次出现位置
                last2 = i  # 更新 2 的最后一次出现位置
            else:  # 遇到数值 3
                first3 = min(first3, i)  # 更新 3 的第一次出现位置
        if first3 < last1:  # 若 3 出现在 1 之前，仅靠解除锁定无法排成有序
            return -1  # 该矛盾无解，返回 -1
        return sum(  # 统计落在必解锁区间内的锁定下标个数并返回
            st and (first2 <= i < last1 or first3 <= i < last2)  # st 为锁定标记且下标落在必解锁区间时计 1
            for i, st in enumerate(locked)  # 遍历每个下标与对应的锁定状态
        )  # 对全部贡献求和
