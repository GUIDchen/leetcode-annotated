# 题目：1981. 最小化目标值与所选元素的差（Minimize the Difference Between Target and Chosen Elements）
# 思路：用布尔可达性数组做逐行背包，每行所有元素都允许重复选，把旧表整体右移 x 位与进新表，最后取与 target 差值最小的可达和。
# 时间复杂度：O(m·n·S)，S 为可能出现的最大和；空间复杂度：O(S)，两张滚动数组。
class Solution:  # LeetCode 约定的题解类
    def minimizeTheDifference(self, mat: List[List[int]], target: int) -> int:  # mat 是二维矩阵，target 是目标值，返回每行选一个数后与 target 的最小绝对差
        f = [True]  # f[j]：前若干行每行选一个数能否凑出和 j，初始只有 0 可达
        for row in mat:  # 逐行往下递推
            mx = max(row)  # 本行最大值，决定新表的最大下标
            g = [False] * (len(f) + mx)  # 新的可达性表，长度在旧表基础上加 mx
            for x in row:  # 枚举本行可以选中的元素 x
                for j in range(x, len(f) + x):  # 把旧表整体右移 x 位写入新表，先算新表可避免原地覆盖
                    g[j] |= f[j - x]  # 若 j-x 可达，则再加上 x 后 j 也可达
            f = g  # 用新表滚动替换旧表
        return min(abs(j - target) for j, ok in enumerate(f) if ok)  # 在所有可达的和里，取与 target 差的绝对值最小者
