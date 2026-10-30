# 题目：3801. 合并有序列表的最小成本（Minimum Cost to Merge Sorted Lists）
# 思路：预处理每个子集的中位数，再对子集做区间 DP：f[mask] = min(f[j] + f[mask^j] + |med[j] - med[mask^j]|) + 元素个数。
# 时间复杂度：O(2^n · n · log V)，枚举子集并二分中位数；空间复杂度：O(2^n)，存放每个子集的计数、中位数与 DP 值。
class Solution:  # LeetCode 约定的题解类
    def minMergeCost(self, lists: List[List[int]]) -> int:  # lists 中每个子数组都已升序，返回合并成一个数组的最小成本
        n = len(lists)  # 子数组个数
        vals = sorted({x for v in lists for x in v})  # 收集所有出现过的数值，去重并排序
        cnt = [0] * (1 << n)  # cnt[mask]：mask 内所有子数组的元素总数
        med = [0] * (1 << n)  # med[mask]：mask 内所有元素的（下）中位数
        for i in range(1, 1 << n):  # 从小到大枚举每个非空子集 mask
            for j, v in enumerate(lists):  # 检查 mask 的每一位
                if i >> j & 1:  # 第 j 个子数组在 mask 里
                    cnt[i] += len(v)  # 累加该子数组的元素个数
            need = (cnt[i] + 1) // 2  # 中位数在全体元素中的排名（向下取整的中位）
            l, r = 0, len(vals) - 1  # 在去重后的数值上二分，l、r 为左右边界
            while l < r:  # 找到最小的下标 l，使「≤ vals[l] 的元素个数 ≥ need」
                mid = (l + r) >> 1  # 二分中点
                le = 0  # 统计 ≤ vals[mid] 的元素个数
                b = i  # 复制 mask，用于逐位遍历
                while b:  # 遍历 mask 的所有置位
                    t = (b & -b).bit_length() - 1  # 最低置位对应的子数组下标
                    le += bisect_right(lists[t], vals[mid])  # 累加该子数组中 ≤ vals[mid] 的元素个数
                    if le >= need:  # 个数已经够用
                        break  # 提前结束统计
                    b &= b - 1  # 消掉最低置位，继续下一位
                if le >= need:  # 数量够，答案可以更小
                    r = mid  # 收缩右边界
                else:  # 数量不够
                    l = mid + 1  # 增大左边界
            med[i] = vals[l]  # 记录该子集的中位数

        f = [inf] * (1 << n)  # f[mask]：把 mask 内子数组合并成一个数组的最小代价
        for i in range(1, 1 << n):  # 枚举每个非空子集
            if i.bit_count() == 1:  # 只有一个子数组
                f[i] = 0  # 无需合并，代价为 0
                continue  # 直接处理下一个子集
            j = (i - 1) & i  # 从 i 的最大真子集开始枚举
            while j:  # 枚举 i 的所有非空真子集 j
                k = i ^ j  # k 是 i 中除去 j 剩下的部分
                if j <= k:  # 只算一次，避免 (j,k) 与 (k,j) 重复
                    f[i] = min(f[i], f[j] + f[k] + abs(med[j] - med[k]))  # 先分别合并两半，再付出两半中位数之差的代价
                j = (j - 1) & i  # 得到下一个更小的真子集
            f[i] += cnt[i]  # 新合并出的数组每个元素都要付出一次代价，共 cnt[i]
        return f[-1]  # 全部子数组合并成一个数组的结果
