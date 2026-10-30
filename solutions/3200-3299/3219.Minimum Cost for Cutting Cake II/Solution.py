# 题目：3219. 切蛋糕的最小总开销 II（Minimum Cost for Cutting Cake II）
# 思路：与 I 相同的双指针贪心；Python 整数天然任意精度，所以代码与 I 完全一致，无需处理溢出。
# 时间复杂度：O(m log m + n log n)，主要是两次排序；空间复杂度：O(m + n)，Timsort 最坏需要 O(n) 的辅助缓冲。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(  # m、n 是蛋糕行列数；两个列表分别是横切、竖切的单价
        self, m: int, n: int, horizontalCut: List[int], verticalCut: List[int]  # 参数换行是 black 的格式化结果，含义不变
    ) -> int:  # 返回最小总开销
        horizontalCut.sort(reverse=True)  # 横切价格原地降序，保证先处理贵的切法
        verticalCut.sort(reverse=True)  # 竖切价格原地降序
        ans = i = j = 0  # ans 累计开销；i、j 分别指向两种切法中还没用过的最大价格
        h = v = 1  # h：横切一次要穿过的竖块数；v：竖切一次要穿过的横块数，最初蛋糕只有 1 块
        while i < m - 1 or j < n - 1:  # 只要还有切法没用完就继续循环
            if j == n - 1 or (i < m - 1 and horizontalCut[i] > verticalCut[j]):  # 竖切已经用完，或横切单价更高时，选择横切
                ans += horizontalCut[i] * v  # 横切费用 = 单价 × 当前竖块数（Python 大整数不会溢出）
                h, i = h + 1, i + 1  # 横切后层数加一（以后竖切要多穿一块），横切指针后移
            else:  # 否则选择竖切
                ans += verticalCut[j] * h  # 竖切费用 = 单价 × 当前横块数
                v, j = v + 1, j + 1  # 竖切后条数加一（以后横切要多穿一块），竖切指针后移
        return ans  # 返回最小总开销
