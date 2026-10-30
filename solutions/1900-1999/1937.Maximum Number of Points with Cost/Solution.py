# 题目：1937. 扣分后的最大得分（Maximum Number of Points with Cost）
# 思路：逐行 DP，把转移代价 |j-k| 拆成 f[k]+k 与 f[k]-k 两种形式，用左右两遍扫描取前缀最大值。
# 时间复杂度：O(mn)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def maxPoints(self, points: List[List[int]]) -> int:  # 返回按行取格子能获得的最大得分
        n = len(points[0])  # 列数，每一行长度都相同
        f = points[0][:]  # 第一行的得分就是格子本身的值，切片复制避免改动入参
        for p in points[1:]:  # 从第二行开始逐行递推
            g = [0] * n  # 当前行的 DP 数组
            lmx = -inf  # 从左扫描时维护的最优前缀值
            for j in range(n):  # 从左往右扫描
                lmx = max(lmx, f[j] + j)  # 把 f[k] - (j - k) 改写成 (f[k] + k) - j，就能用前缀最大值一次取到最优来源
                g[j] = max(g[j], p[j] + lmx - j)  # 用左侧最优来源更新当前格
            rmx = -inf  # 从右扫描时维护的最优前缀值
            for j in range(n - 1, -1, -1):  # 从右往左扫描
                rmx = max(rmx, f[j] - j)  # 对称地维护 (f[k] - k) 的前缀最大值
                g[j] = max(g[j], p[j] + rmx + j)  # 用右侧最优来源更新当前格
            f = g  # 滚动：把当前行结果当作上一行
        return max(f)  # 最后一行的最大得分就是答案
