# 题目：1658. 将 x 减到 0 的最小操作数（Minimum Operations to Reduce X to Zero）
# 思路：从两端删除等价于保留中间一段和恰为 sum - x 的连续子数组，求这段子数组的最大长度即可。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，字典最多存 n 个前缀和。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], x: int) -> int:  # nums：输入数组；x：目标值；返回把 x 减到 0 的最少操作数
        s = sum(nums) - x  # 总和减 x 就是中间保留段应有的和：删两端等价于留中间
        vis = {0: -1}  # 前缀和 → 最早下标；0: -1 是哨兵，表示空前缀和
        mx, t = -1, 0  # mx 存保留段最长长度，t 是滚动前缀和
        for i, v in enumerate(nums):  # 枚举右端点，同时拿到下标 i 与元素值 v
            t += v  # 累加前缀和
            if t not in vis:  # 同一前缀和只记第一次出现的位置，越靠左窗口越长
                vis[t] = i  # 记录该前缀和对应的最早下标
            if t - s in vis:  # 若前缀和 t - s 出现过，说明存在和为 s 的连续段
                mx = max(mx, i - vis[t - s])  # 用当前窗口长度更新最长保留段
        return -1 if mx == -1 else len(nums) - mx  # 无解返回 -1，否则总长减去保留段长即为最少操作次数
