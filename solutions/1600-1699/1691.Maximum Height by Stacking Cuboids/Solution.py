# 题目：1691. 堆叠长方体的最大高度（Maximum Height by Stacking Cuboids）
# 思路：先把每个长方体的三边升序排列（最小的两条作底面、最大的作高），整体排序后用最长上升子序列式 DP 求最大堆叠高度。
# 时间复杂度：O(n^2) 的 DP 转移（排序 O(n log n)）；空间复杂度：O(n) 的 DP 数组 f。
class Solution:  # LeetCode 约定的题解类
    def maxHeight(self, cuboids: List[List[int]]) -> int:  # cuboids[i] 是第 i 个长方体的三个维度
        for c in cuboids:  # 逐个体处理
            c.sort()  # 三边升序排列：最小两条作底面，最大一条作高
        cuboids.sort()  # 整体字典序排序，使能垫在下面的长方体排在前面
        n = len(cuboids)  # 长方体个数
        f = [0] * n  # f[i]：以第 i 个长方体作堆顶时的最大总高度
        for i in range(n):  # 依次把第 i 个长方体当作堆顶
            for j in range(i):  # 枚举可能垫在它下面的长方体 j
                if cuboids[j][1] <= cuboids[i][1] and cuboids[j][2] <= cuboids[i][2]:  # 两个底面维度都不超过上方长方体才能堆叠
                    f[i] = max(f[i], f[j])  # 继承下面那一摞的最大高度
            f[i] += cuboids[i][2]  # 加上自身高度
        return max(f)  # 所有堆法中的最大高度
